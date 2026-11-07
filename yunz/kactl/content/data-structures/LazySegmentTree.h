/**
 * Description: 懒标记线段树, 下标 a[1..n]. 默认: 区间加, 查区间和与区间最大值.
 * 换用途只改 Node 的字段, operator+, build 的叶子, 标记数组, addtag 和 pushdown,
 * 写法见下方懒标记写法. query 只合并非空的两半, 所以不需要单位元.
 * Usage: n = ...; for (int i = 1; i <= n; i++) a[i] = ...;
 * build(1, 1, n); // 多组数据重新 build 即可, 会清空 lz
 * update(1, 1, n, l, r, v); // a[l..r] 都加 v
 * Node q = query(1, 1, n, l, r); // q.sum, q.mx
 * Time: O(\log N)
 */
#pragma once

const int N=2e5+5;
ll a[N];
struct Node{ll sum,mx;};
Node t[N<<2];
ll lz[N<<2]; // 整段待加的值
Node operator+(Node x,Node y){ // 合并左右儿子
	return {x.sum+y.sum,max(x.mx,y.mx)};
}
void pushup(int p){t[p]=t[p<<1]+t[p<<1|1];}
void addtag(int p,int l,int r,ll v){ // 整段 [l, r] 都加 v
	t[p].sum+=v*(r-l+1),t[p].mx+=v;
	lz[p]+=v;
}
void pushdown(int p,int l,int r){
	if(!lz[p])return;
	int m=(l+r)>>1;
	addtag(p<<1,l,m,lz[p]),addtag(p<<1|1,m+1,r,lz[p]);
	lz[p]=0;
}
void build(int p,int l,int r){
	lz[p]=0;
	if(l==r){t[p]={a[l],a[l]};return;}
	int m=(l+r)>>1;
	build(p<<1,l,m),build(p<<1|1,m+1,r);
	pushup(p);
}
void update(int p,int l,int r,int x,int y,ll v){ // 加 v
	if(x<=l&&r<=y){addtag(p,l,r,v);return;}
	pushdown(p,l,r);
	int m=(l+r)>>1;
	if(x<=m)update(p<<1,l,m,x,y,v);
	if(y>m)update(p<<1|1,m+1,r,x,y,v);
	pushup(p);
}
Node query(int p,int l,int r,int x,int y){ // [x, y]
	if(x<=l&&r<=y)return t[p];
	pushdown(p,l,r);
	int m=(l+r)>>1;
	if(y<=m)return query(p<<1,l,m,x,y);
	if(x>m)return query(p<<1|1,m+1,r,x,y);
	return query(p<<1,l,m,x,y)+query(p<<1|1,m+1,r,x,y);
}
