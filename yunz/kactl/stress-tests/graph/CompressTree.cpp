#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/CompressTree.h"

mt19937 rng(37);
int R(int a,int b){return rng()%(b-a+1)+a;}

const int N=2e5+5;
int dfn[N],par[N],dep[N],tim;
vector<int> G[N];
void dfs(int u,int f){
	dfn[u]=++tim;par[u]=f;dep[u]=dep[f]+1;
	for(int v:G[u])if(v!=f)dfs(v,u);
}
int lca(int x,int y){
	while(x!=y){if(dep[x]<dep[y])swap(x,y);x=par[x];}
	return x;
}
int h[N];

int main(){
	long long checks=0;
	for(int it=0;it<3000;it++){
		int n=R(1,60);
		for(int i=1;i<=n;i++)G[i].clear();
		vector<int> perm(n+1);iota(perm.begin(),perm.end(),0);
		shuffle(perm.begin()+2,perm.end(),rng); // keep 1 as root label
		for(int i=2;i<=n;i++){
			int p=it%4==0?i-1:R(1,i-1);
			G[perm[i]].push_back(perm[p]),G[perm[p]].push_back(perm[i]);
		}
		tim=0;dfs(1,0);
		for(int q=0;q<20;q++){
			int k=R(1,min(n,10));
			vector<int> all(n);iota(all.begin(),all.end(),1);
			shuffle(all.begin(),all.end(),rng);
			for(int i=1;i<=k;i++)h[i]=all[i-1];
			vector<int> keys(h+1,h+k+1);
			VT.build(h,k);
			// brute: S = keys + root + pairwise lca
			set<int> S(keys.begin(),keys.end());S.insert(1);
			for(int x:keys)for(int y:keys)S.insert(lca(x,y));
			set<pair<int,int>> exp,got;
			for(int x:S)if(x!=1){
				int y=par[x];while(!S.count(y))y=par[y];
				exp.insert({y,x});
			}
			set<int> vsSet;
			for(int i=1;i<=VT.vn;i++){assert(!vsSet.count(VT.vs[i]));vsSet.insert(VT.vs[i]);}
			assert(vsSet==S);
			for(int i=1;i<=VT.vn;i++)for(int v:VT.vt[VT.vs[i]]){
				assert(!got.count({VT.vs[i],v}));got.insert({VT.vs[i],v});
			}
			assert(exp==got);
			assert(VT.vn<=2*k);
			checks++;
		}
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
