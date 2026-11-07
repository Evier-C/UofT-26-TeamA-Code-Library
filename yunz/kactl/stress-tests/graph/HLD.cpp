#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// simple lazy segment tree standing in for the user's one
const int SN=2e5+5;
ll t[SN<<2],lz[SN<<2];int segn;
void pushdown(int p,int l,int r){
	if(!lz[p])return;int mid=(l+r)/2;
	t[p*2]+=lz[p]*(mid-l+1),lz[p*2]+=lz[p];
	t[p*2+1]+=lz[p]*(r-mid),lz[p*2+1]+=lz[p];lz[p]=0;
}
void build(int p,int l,int r,ll*a){
	lz[p]=0;
	if(l==r){t[p]=a[l];return;}
	int mid=(l+r)/2;build(p*2,l,mid,a);build(p*2+1,mid+1,r,a);t[p]=t[p*2]+t[p*2+1];
}
void update(int p,int l,int r,int ql,int qr,ll v){
	if(ql<=l&&r<=qr){t[p]+=v*(r-l+1);lz[p]+=v;return;}
	pushdown(p,l,r);int mid=(l+r)/2;
	if(ql<=mid)update(p*2,l,mid,ql,qr,v);
	if(qr>mid)update(p*2+1,mid+1,r,ql,qr,v);
	t[p]=t[p*2]+t[p*2+1];
}
ll query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return t[p];
	pushdown(p,l,r);int mid=(l+r)/2;ll s=0;
	if(ql<=mid)s+=query(p*2,l,mid,ql,qr);
	if(qr>mid)s+=query(p*2+1,mid+1,r,ql,qr);
	return s;
}
void upd(int l,int r,ll v){update(1,1,segn,l,r,v);}
ll qry(int l,int r){return query(1,1,segn,l,r);}
#include "../../content/graph/HLD.h"

mt19937 rng(41);
int R(int a,int b){return rng()%(b-a+1)+a;}
ll a[SN],b[SN],val[SN];
int par[SN],dp[SN];

int main(){
	long long checks=0;
	for(int it=0;it<400;it++){
		bool big=it>=395;
		int n=big?R(5000,5000):R(1,40),rt=R(1,n);
		segn=n;
		H.init(n);
		vector<int> perm(n+1);iota(perm.begin(),perm.end(),0);
		shuffle(perm.begin()+1,perm.end(),rng);
		for(int i=2;i<=n;i++){
			int p=it%3==0?i-1:R(1,i-1);
			H.g[perm[i]].push_back(perm[p]),H.g[perm[p]].push_back(perm[i]);
		}
		for(int i=1;i<=n;i++)a[i]=val[i]=R(-1000,1000);
		H.dfs1(rt,0);H.dfs2(rt,rt);
		for(int i=1;i<=n;i++)b[i]=a[H.rnk[i]];
		build(1,1,n,b);
		// brute parent/depth
		{
			vector<int> st={rt};par[rt]=0;dp[rt]=0;vector<int> vis(n+1);vis[rt]=1;
			while(!st.empty()){int u=st.back();st.pop_back();
				for(int v:H.g[u])if(!vis[v])vis[v]=1,par[v]=u,dp[v]=dp[u]+1,st.push_back(v);}
		}
		auto blca=[&](int x,int y){while(x!=y){if(dp[x]<dp[y])swap(x,y);x=par[x];}return x;};
		auto inSub=[&](int y,int x){while(y&&y!=x)y=par[y];return y==x;};
		int Q=big?2000:200;
		for(int q=0;q<Q;q++){
			int op=R(0,4),x=R(1,n),y=R(1,n);ll v=R(-100,100);
			if(op==0){
				assert(H.lca(x,y)==blca(x,y));
			}else if(op==1){
				H.updPath(x,y,v);
				int l=blca(x,y);
				for(int z=x;z!=l;z=par[z])val[z]+=v;
				for(int z=y;z!=l;z=par[z])val[z]+=v;
				val[l]+=v;
			}else if(op==2){
				int l=blca(x,y);ll s=val[l];
				for(int z=x;z!=l;z=par[z])s+=val[z];
				for(int z=y;z!=l;z=par[z])s+=val[z];
				assert(H.qryPath(x,y)==s);
			}else if(op==3){
				H.updSub(x,v);
				for(int z=1;z<=n;z++)if(inSub(z,x))val[z]+=v;
				if(big)q+=50;
			}else{
				ll s=0;for(int z=1;z<=n;z++)if(inSub(z,x))s+=val[z];
				assert(H.qrySub(x)==s);
				if(big)q+=50;
			}
			checks++;
		}
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
