#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/Dinic.h"

mt19937 rng(12345);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}

// brute force: Edmonds-Karp on capacity matrix (1-indexed)
ll bruteFlow(int nn,vector<vector<ll>>c,int s,int t){
	ll f=0;
	while(true){
		vector<int>par(nn+1,0);par[s]=s;
		queue<int>q;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int v=1;v<=nn;v++)if(!par[v]&&c[u][v]>0)par[v]=u,q.push(v);
		}
		if(!par[t])return f;
		ll d=LLONG_MAX;
		for(int v=t;v!=s;v=par[v])d=min(d,c[par[v]][v]);
		for(int v=t;v!=s;v=par[v])c[par[v]][v]-=d,c[v][par[v]]+=d;
		f+=d;
	}
}
// exhaustive maximum bipartite matching: dp over left, mask of right
int bruteMatch(int L,int R,vector<pair<int,int>>&ed){
	vector<vector<int>>adj(L+1);
	for(auto[a,b]:ed)adj[a].push_back(b);
	vector<int>dp(1<<R,-1);dp[0]=0;
	for(int i=1;i<=L;i++){
		vector<int>nd=dp;
		for(int m=0;m<(1<<R);m++)if(dp[m]>=0)
			for(int b:adj[i])if(!(m>>(b-1)&1))
				nd[m|1<<(b-1)]=max(nd[m|1<<(b-1)],dp[m]+1);
		dp=nd;
	}
	return *max_element(dp.begin(),dp.end());
}
long long checks=0;
void testFlow(int nn,int mm,int maxc){
	int s=rnd(1,nn),t=rnd(1,nn-1);if(t>=s)t++;
	init(nn);
	vector<array<ll,3>>E;vector<int>id;
	vector<vector<ll>>c(nn+1,vector<ll>(nn+1,0));
	for(int i=0;i<mm;i++){
		int u=rnd(1,nn),v=rnd(1,nn);ll w=rnd(0,maxc);
		E.push_back({u,v,w});id.push_back(add(u,v,w));
		if(u!=v)c[u][v]+=w;
	}
	ll f=dinic(s,t);
	assert(f==bruteFlow(nn,c,s,t));
	// per-edge flows: capacity and conservation
	vector<ll>bal(nn+1,0);
	for(int i=0;i<mm;i++){
		ll fe=cap[id[i]^1];
		assert(0<=fe&&fe<=E[i][2]);
		assert(cap[id[i]]+fe==E[i][2]);
		bal[E[i][0]]-=fe;bal[E[i][1]]+=fe;
	}
	for(int v=1;v<=nn;v++){
		if(v==s)assert(bal[v]==-f);
		else if(v==t)assert(bal[v]==f);
		else assert(bal[v]==0);
	}
	// min cut from dep[]
	assert(dep[s]&&!dep[t]);
	ll cut=0;
	for(int i=0;i<mm;i++){
		int u=E[i][0],v=E[i][1];
		if(dep[u]&&!dep[v])cut+=E[i][2],assert(cap[id[i]]==0);
		if(!dep[u]&&dep[v])assert(cap[id[i]^1]==0);
	}
	assert(cut==f);
	checks++;
}
void testMatch(int L,int R,int mm){
	int s=L+R+1,t=L+R+2;
	init(L+R+2);
	for(int i=1;i<=L;i++)add(s,i,1);
	for(int j=1;j<=R;j++)add(L+j,t,1);
	vector<pair<int,int>>ed;vector<int>id;
	for(int k=0;k<mm;k++){
		int a=rnd(1,L),b=rnd(1,R);
		ed.push_back({a,b});id.push_back(add(a,L+b,1));
	}
	ll f=dinic(s,t);
	if(R<=12)assert(f==bruteMatch(L,R,ed));
	vector<int>uL(L+1),uR(R+1);int got=0;
	for(int k=0;k<mm;k++)if(cap[id[k]]==0){
		auto[a,b]=ed[k];
		assert(!uL[a]&&!uR[b]);uL[a]=uR[b]=1;got++;
	}
	assert(got==f);
	checks++;
}
int main(){
	for(int it=0;it<100000;it++)testFlow(rnd(2,8),rnd(0,20),rnd(0,1)?3:1000);
	for(int it=0;it<300;it++)testFlow(rnd(2,80),rnd(0,600),rnd(0,1)?1:(int)1e9);
	for(int it=0;it<20000;it++)testMatch(rnd(1,8),rnd(1,8),rnd(0,20));
	for(int it=0;it<200;it++)testMatch(rnd(1,12),rnd(1,12),rnd(0,60));
	for(int it=0;it<5;it++)testMatch(3000,3000,30000);
	cout<<"checks: "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
