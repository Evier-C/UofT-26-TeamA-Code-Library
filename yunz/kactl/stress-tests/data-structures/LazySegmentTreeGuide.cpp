// Checks the default LazySegmentTree.h and every code block of the lazy-tag guide
// in content/data-structures/chapter.tex against brute force. Each variant is the
// template with that block's changes applied (blocks copied verbatim, marked below).
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace V0{
#include "../../content/data-structures/LazySegmentTree.h"
}
namespace V1{
const int N=2e5+5;
ll a[N];
struct Node{ll sum,mx;};
Node t[N<<2];
Node operator+(Node x,Node y){
	return {x.sum+y.sum,max(x.mx,y.mx)};
}
void pushup(int p){t[p]=t[p<<1]+t[p<<1|1];}
// ---- guide block 1 (copied verbatim) ----
// 标记: tg[p] 为 1 表示整段待赋成 lz[p]
ll lz[N<<2];bool tg[N<<2]; // build 里清 0
void addtag(int p,int l,int r,ll v){ // 整段赋成 v
	t[p].sum=v*(r-l+1),t[p].mx=v;
	lz[p]=v,tg[p]=1; // 新赋值直接覆盖旧标记
}
void pushdown(int p,int l,int r){
	if(!tg[p])return;
	int m=(l+r)>>1;
	addtag(p<<1,l,m,lz[p]),addtag(p<<1|1,m+1,r,lz[p]);
	tg[p]=0;
}
// ---- end of block ----
void build(int p,int l,int r){
	lz[p]=0,tg[p]=0;
	if(l==r){t[p]={a[l],a[l]};return;}
	int m=(l+r)>>1;
	build(p<<1,l,m),build(p<<1|1,m+1,r);
	pushup(p);
}
void update(int p,int l,int r,int x,int y,ll v){
	if(x<=l&&r<=y){addtag(p,l,r,v);return;}
	pushdown(p,l,r);
	int m=(l+r)>>1;
	if(x<=m)update(p<<1,l,m,x,y,v);
	if(y>m)update(p<<1|1,m+1,r,x,y,v);
	pushup(p);
}
Node query(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return t[p];
	pushdown(p,l,r);
	int m=(l+r)>>1;
	if(y<=m)return query(p<<1,l,m,x,y);
	if(x>m)return query(p<<1|1,m+1,r,x,y);
	return query(p<<1,l,m,x,y)+query(p<<1|1,m+1,r,x,y);
}
}
namespace V2{
const int N=2e5+5;
ll a[N];
struct Node{ll sum,mx;};
Node t[N<<2];
Node operator+(Node x,Node y){
	return {x.sum+y.sum,max(x.mx,y.mx)};
}
void pushup(int p){t[p]=t[p<<1]+t[p<<1|1];}
// ---- guide block 2 (copied verbatim) ----
// 标记: 若 tg[p] 先整段赋成 sv[p], 再整段加 ad[p]
ll sv[N<<2],ad[N<<2];bool tg[N<<2]; // build 里清 0
void setv(int p,int l,int r,ll v){ // 整段赋成 v
	t[p].sum=v*(r-l+1),t[p].mx=v;
	sv[p]=v,tg[p]=1,ad[p]=0;
}
void addv(int p,int l,int r,ll v){ // 整段加 v
	t[p].sum+=v*(r-l+1),t[p].mx+=v;
	ad[p]+=v;
}
void pushdown(int p,int l,int r){
	int m=(l+r)>>1;
	if(tg[p]){
		setv(p<<1,l,m,sv[p]),setv(p<<1|1,m+1,r,sv[p]);
		tg[p]=0;
	}
	if(ad[p]){
		addv(p<<1,l,m,ad[p]),addv(p<<1|1,m+1,r,ad[p]);
		ad[p]=0;
	}
}
void update(int p,int l,int r,int x,int y,int op,ll v){
	if(x<=l&&r<=y){
		if(op)setv(p,l,r,v);
		else addv(p,l,r,v);
		return;
	} // 其余同模板, 递归时也传 op
// ---- end of block ----
	pushdown(p,l,r);
	int m=(l+r)>>1;
	if(x<=m)update(p<<1,l,m,x,y,op,v);
	if(y>m)update(p<<1|1,m+1,r,x,y,op,v);
	pushup(p);
}
void build(int p,int l,int r){
	sv[p]=ad[p]=0,tg[p]=0;
	if(l==r){t[p]={a[l],a[l]};return;}
	int m=(l+r)>>1;
	build(p<<1,l,m),build(p<<1|1,m+1,r);
	pushup(p);
}
Node query(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return t[p];
	pushdown(p,l,r);
	int m=(l+r)>>1;
	if(y<=m)return query(p<<1,l,m,x,y);
	if(x>m)return query(p<<1|1,m+1,r,x,y);
	return query(p<<1,l,m,x,y)+query(p<<1|1,m+1,r,x,y);
}
}
namespace V3{
const int N=2e5+5;
ll a[N];
// ---- guide block 3 (copied verbatim) ----
const ll M=998244353;
struct Node{ll sum;};
Node operator+(Node x,Node y){return {(x.sum+y.sum)%M};}
// 标记: 整段每个数先乘 mu[p] 再加 ad[p]
Node t[N<<2];
void pushup(int p){t[p]=t[p<<1]+t[p<<1|1];}
ll mu[N<<2],ad[N<<2]; // build 里 mu[p]=1,ad[p]=0
// 叶子 t[p]={a[l]%M}, 不要 mx
void addtag(int p,int l,int r,ll k,ll b){
	t[p].sum=(k*t[p].sum+b*(r-l+1))%M;
	mu[p]=mu[p]*k%M,ad[p]=(ad[p]*k+b)%M;
}
void pushdown(int p,int l,int r){
	if(mu[p]==1&&!ad[p])return;
	int m=(l+r)>>1;
	addtag(p<<1,l,m,mu[p],ad[p]);
	addtag(p<<1|1,m+1,r,mu[p],ad[p]);
	mu[p]=1,ad[p]=0;
}
// update 的参数 v 换成 k, b, 命中整段时 addtag(p,l,r,k,b)
// ---- end of block ----
void build(int p,int l,int r){
	mu[p]=1,ad[p]=0;
	if(l==r){t[p]={a[l]%M};return;}
	int m=(l+r)>>1;
	build(p<<1,l,m),build(p<<1|1,m+1,r);
	pushup(p);
}
void update(int p,int l,int r,int x,int y,ll k,ll b){
	if(x<=l&&r<=y){addtag(p,l,r,k,b);return;}
	pushdown(p,l,r);
	int m=(l+r)>>1;
	if(x<=m)update(p<<1,l,m,x,y,k,b);
	if(y>m)update(p<<1|1,m+1,r,x,y,k,b);
	pushup(p);
}
Node query(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return t[p];
	pushdown(p,l,r);
	int m=(l+r)>>1;
	if(y<=m)return query(p<<1,l,m,x,y);
	if(x>m)return query(p<<1|1,m+1,r,x,y);
	return query(p<<1,l,m,x,y)+query(p<<1|1,m+1,r,x,y);
}
}
namespace V4{
const int N=2e5+5;
ll a[N];
// ---- guide block 4 (copied verbatim) ----
struct Node{int cnt;}; // 区间里 1 的个数
Node operator+(Node x,Node y){return {x.cnt+y.cnt};}
Node t[N<<2];
void pushup(int p){t[p]=t[p<<1]+t[p<<1|1];}
bool rev[N<<2]; // 取反标记, build 里清 0
// 叶子 t[p]={(int)a[l]}
void addtag(int p,int l,int r){ // 整段 0 和 1 互换
	t[p].cnt=(r-l+1)-t[p].cnt,rev[p]^=1;
}
void pushdown(int p,int l,int r){
	if(!rev[p])return;
	int m=(l+r)>>1;
	addtag(p<<1,l,m),addtag(p<<1|1,m+1,r);
	rev[p]=0;
}
// update 去掉参数 v, 命中整段时 addtag(p,l,r)
// ---- end of block ----
void build(int p,int l,int r){
	rev[p]=0;
	if(l==r){t[p]={(int)a[l]};return;}
	int m=(l+r)>>1;
	build(p<<1,l,m),build(p<<1|1,m+1,r);
	pushup(p);
}
void update(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y){addtag(p,l,r);return;}
	pushdown(p,l,r);
	int m=(l+r)>>1;
	if(x<=m)update(p<<1,l,m,x,y);
	if(y>m)update(p<<1|1,m+1,r,x,y);
	pushup(p);
}
Node query(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return t[p];
	pushdown(p,l,r);
	int m=(l+r)>>1;
	if(y<=m)return query(p<<1,l,m,x,y);
	if(x>m)return query(p<<1|1,m+1,r,x,y);
	return query(p<<1,l,m,x,y)+query(p<<1|1,m+1,r,x,y);
}
}
namespace V5{
const int N=2e5+5;
ll a[N];
// ---- guide block 5 (copied verbatim) ----
struct Node{ll sum,pre,suf,best;}; // 前缀, 后缀, 答案
Node operator+(Node x,Node y){
	return {x.sum+y.sum,max(x.pre,x.sum+y.pre),
	        max(y.suf,y.sum+x.suf),
	        max({x.best,y.best,x.suf+y.pre})};
}
// 叶子 t[p]={a[l],a[l],a[l],a[l]}
// 删去 lz, addtag, pushdown 及其所有调用
Node t[N<<2];
void pushup(int p){t[p]=t[p<<1]+t[p<<1|1];}
void modify(int p,int l,int r,int x,ll v){ // a[x] 赋成 v
	if(l==r){t[p]={v,v,v,v};return;}
	int m=(l+r)>>1;
	if(x<=m)modify(p<<1,l,m,x,v);
	else modify(p<<1|1,m+1,r,x,v);
	pushup(p);
}
// ---- end of block ----
void build(int p,int l,int r){
	// no tags
	if(l==r){t[p]={a[l],a[l],a[l],a[l]};return;}
	int m=(l+r)>>1;
	build(p<<1,l,m),build(p<<1|1,m+1,r);
	pushup(p);
}
Node query(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return t[p];
	int m=(l+r)>>1;
	if(y<=m)return query(p<<1,l,m,x,y);
	if(x>m)return query(p<<1|1,m+1,r,x,y);
	return query(p<<1,l,m,x,y)+query(p<<1|1,m+1,r,x,y);
}
}

mt19937 rng(7);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}
long long checks=0;
const ll MOD=998244353;

int main(){
	for(int it=0;it<1500;it++){
		bool big=it>=1490;
		int n=big?rnd(1000,200000):rnd(1,40),steps=big?3000:200;
		auto rg=[&](int&l,int&r){
			l=rnd(1,n),r=rnd(l,n);
			if(big&&rng()%100)r=min(n,l+rnd(0,30));
		};
		vector<ll>b(n+1);
		// V0: default range add
		for(int i=1;i<=n;i++)b[i]=V0::a[i]=rnd(-1000,1000);
		V0::build(1,1,n);
		for(int s=0;s<steps;s++){
			int l,r;rg(l,r);
			if(rng()%2){
				ll v=rnd(-1000,1000);V0::update(1,1,n,l,r,v);
				for(int i=l;i<=r;i++)b[i]+=v;
			}else{
				V0::Node q=V0::query(1,1,n,l,r);ll sm=0,mx=LLONG_MIN;
				for(int i=l;i<=r;i++)sm+=b[i],mx=max(mx,b[i]);
				assert(q.sum==sm&&q.mx==mx);checks++;
			}
		}
		// V1: range assign
		for(int i=1;i<=n;i++)b[i]=V1::a[i]=rnd(-1000,1000);
		V1::build(1,1,n);
		for(int s=0;s<steps;s++){
			int l,r;rg(l,r);
			if(rng()%2){
				ll v=rnd(-1000,1000);V1::update(1,1,n,l,r,v);
				for(int i=l;i<=r;i++)b[i]=v;
			}else{
				V1::Node q=V1::query(1,1,n,l,r);ll sm=0,mx=LLONG_MIN;
				for(int i=l;i<=r;i++)sm+=b[i],mx=max(mx,b[i]);
				assert(q.sum==sm&&q.mx==mx);checks++;
			}
		}
		// V2: assign + add
		for(int i=1;i<=n;i++)b[i]=V2::a[i]=rnd(-1000,1000);
		V2::build(1,1,n);
		for(int s=0;s<steps;s++){
			int l,r;rg(l,r);
			int c=rng()%3;
			if(c<2){
				ll v=rnd(-1000,1000);V2::update(1,1,n,l,r,c,v);
				for(int i=l;i<=r;i++)b[i]=c?v:b[i]+v;
			}else{
				V2::Node q=V2::query(1,1,n,l,r);ll sm=0,mx=LLONG_MIN;
				for(int i=l;i<=r;i++)sm+=b[i],mx=max(mx,b[i]);
				assert(q.sum==sm&&q.mx==mx);checks++;
			}
		}
		// V3: multiply then add, mod
		for(int i=1;i<=n;i++)b[i]=V3::a[i]=rng()%MOD;
		V3::build(1,1,n);
		for(int s=0;s<steps;s++){
			int l,r;rg(l,r);
			if(rng()%2){
				ll k=rng()%MOD,bb=rng()%MOD;
				if(rng()%4==0)k=rnd(0,2);
				if(rng()%4==0)bb=0;
				V3::update(1,1,n,l,r,k,bb);
				for(int i=l;i<=r;i++)b[i]=(k*b[i]+bb)%MOD;
			}else{
				ll sm=0;
				for(int i=l;i<=r;i++)sm=(sm+b[i])%MOD;
				assert(V3::query(1,1,n,l,r).sum==sm);checks++;
			}
		}
		// V4: 01 flip
		for(int i=1;i<=n;i++)b[i]=V4::a[i]=rnd(0,1);
		V4::build(1,1,n);
		for(int s=0;s<steps;s++){
			int l,r;rg(l,r);
			if(rng()%2){
				V4::update(1,1,n,l,r);
				for(int i=l;i<=r;i++)b[i]^=1;
			}else{
				ll c=0;
				for(int i=l;i<=r;i++)c+=b[i];
				assert(V4::query(1,1,n,l,r).cnt==c);checks++;
			}
		}
		// V5: max subarray sum, point assign
		for(int i=1;i<=n;i++)b[i]=V5::a[i]=rnd(-1000,1000);
		V5::build(1,1,n);
		for(int s=0;s<steps;s++){
			if(rng()%2){
				int x=rnd(1,n);ll v=rnd(-1000,1000);
				V5::modify(1,1,n,x,v);b[x]=v;
			}else{
				int l,r;rg(l,r);
				ll best=LLONG_MIN,cur=0;
				for(int i=l;i<=r;i++){
					cur=max(cur+b[i],b[i]);best=max(best,cur);
				}
				V5::Node q=V5::query(1,1,n,l,r);
				assert(q.best==best);checks++;
				ll sm=0;for(int i=l;i<=r;i++)sm+=b[i];
				assert(q.sum==sm);
			}
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
