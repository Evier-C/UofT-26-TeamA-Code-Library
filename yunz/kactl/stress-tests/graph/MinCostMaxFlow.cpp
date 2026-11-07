#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/MinCostMaxFlow.h"

mt19937 rng(4242);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}

struct E{int u,v;ll c,w;};
// brute force: enumerate every integer flow on every edge
pair<ll,ll>brute(int nn,vector<E>&es,int s,int t){
	int m=es.size();
	vector<ll>f(m,0);
	pair<ll,ll>best={-1,0};
	while(true){
		vector<ll>bal(nn+1,0);ll co=0;
		for(int i=0;i<m;i++)bal[es[i].u]-=f[i],bal[es[i].v]+=f[i],co+=f[i]*es[i].w;
		bool ok=true;
		for(int v=1;v<=nn;v++)if(v!=s&&v!=t&&bal[v])ok=false;
		if(ok){
			ll val=bal[t];
			if(val>best.first||(val==best.first&&co<best.second))best={val,co};
		}
		int i=0;
		while(i<m&&f[i]==es[i].c)f[i]=0,i++;
		if(i==m)break;
		f[i]++;
	}
	return best;
}
long long checks=0;
void test(int nn,int mm,int maxc,int maxw,bool br){
	int s=rnd(1,nn),t=rnd(1,nn-1);if(t>=s)t++;
	vector<ll>p(nn+1);
	for(int v=1;v<=nn;v++)p[v]=rnd(-maxw,maxw);
	vector<E>es;vector<int>id;
	init(nn);
	for(int i=0;i<mm;i++){
		int u=rnd(1,nn),v=rnd(1,nn);
		// cost = base + p[u] - p[v], so no negative cycle
		ll c=rnd(0,maxc),w=rnd(0,maxw)+p[u]-p[v];
		es.push_back({u,v,c,w});id.push_back(add(u,v,c,w));
	}
	auto [f,co]=mcmf(s,t);
	if(br){
		auto b=brute(nn,es,s,t);
		assert(b.first==f&&b.second==co);
	}
	// per-edge flows
	vector<ll>bal(nn+1,0);ll sc=0;
	for(int i=0;i<mm;i++){
		ll fe=cap[id[i]^1];
		assert(0<=fe&&fe<=es[i].c&&cap[id[i]]+fe==es[i].c);
		bal[es[i].u]-=fe;bal[es[i].v]+=fe;sc+=fe*es[i].w;
	}
	for(int v=1;v<=nn;v++)
		assert(bal[v]==(v==s?-f:v==t?f:0));
	assert(sc==co);
	// max: t unreachable; min cut from dis[] equals flow
	assert(dis[s]<INF&&!(dis[t]<INF));
	ll cut=0;
	for(int i=0;i<mm;i++){
		bool a=dis[es[i].u]<INF,b=dis[es[i].v]<INF;
		if(a&&!b)cut+=es[i].c,assert(cap[id[i]]==0);
		if(!a&&b)assert(cap[id[i]^1]==0);
	}
	assert(cut==f);
	// min cost: no negative cycle in residual graph (Bellman-Ford)
	vector<ll>d(nn+1,0);
	for(int it=0;it<=nn;it++){
		bool ch=false;
		for(int e=2;e<=cnt;e++)if(cap[e]&&d[to[e^1]]+cost[e]<d[to[e]])
			d[to[e]]=d[to[e^1]]+cost[e],ch=true;
		if(!ch)break;
		assert(it<nn);
	}
	checks++;
}
// min cost perfect assignment vs permutations
void testAssign(int k){
	vector<vector<ll>>w(k+1,vector<ll>(k+1));
	int L=k,s=2*k+1,t=2*k+2;
	init(2*k+2);
	vector<array<int,3>>id;
	for(int i=1;i<=k;i++)add(s,i,1,0),add(L+i,t,1,0);
	for(int i=1;i<=k;i++)for(int j=1;j<=k;j++){
		w[i][j]=rnd(-50,50);
		id.push_back({add(i,L+j,1,w[i][j]),i,j});
	}
	auto [f,co]=mcmf(s,t);
	assert(f==k);
	vector<int>perm(k);iota(perm.begin(),perm.end(),1);
	ll best=LLONG_MAX;
	do{
		ll c=0;
		for(int i=1;i<=k;i++)c+=w[i][perm[i-1]];
		best=min(best,c);
	}while(next_permutation(perm.begin(),perm.end()));
	assert(best==co);
	vector<int>uR(k+1);ll c=0;int got=0;
	for(auto [e,i,j]:id)if(cap[e]==0)assert(!uR[j]),uR[j]=1,c+=w[i][j],got++;
	assert(got==k&&c==co);
	checks++;
}
int main(){
	for(int it=0;it<30000;it++)test(rnd(2,5),rnd(0,6),2,5,true);
	for(int it=0;it<2000;it++)test(rnd(2,4),rnd(0,8),1,10,true);
	for(int it=0;it<3000;it++)test(rnd(2,30),rnd(0,150),rnd(1,20),100,false);
	for(int it=0;it<20;it++)test(rnd(100,300),rnd(500,3000),1000,1000000,false);
	for(int it=0;it<3000;it++)testAssign(rnd(1,7));
	cout<<"checks: "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
