#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/MinCut.h"

mt19937 rng(777);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}

// brute force min cut: try every vertex subset containing s but not t
ll bruteCut(int nn,vector<array<ll,3>>&E,int s,int t){
	ll best=LLONG_MAX;
	for(int m=0;m<(1<<nn);m++){
		if(!(m>>(s-1)&1)||(m>>(t-1)&1))continue;
		ll c=0;
		for(auto&e:E)if((m>>(e[0]-1)&1)&&!(m>>(e[1]-1)&1))c+=e[2];
		best=min(best,c);
	}
	return best;
}
long long checks=0;
void test(int nn,int mm,int maxc,bool brute){
	int s=rnd(1,nn),t=rnd(1,nn-1);if(t>=s)t++;
	init(nn);
	vector<array<ll,3>>E;map<int,int>idx;
	for(int i=0;i<mm;i++){
		int u=rnd(1,nn),v=rnd(1,nn);ll w=rnd(0,maxc);
		E.push_back({u,v,w});idx[add(u,v,w)]=i;
	}
	ll f=dinic(s,t);
	if(brute)assert(f==bruteCut(nn,E,s,t));
	vector<int>cut=minCut();
	ll sum=0;set<int>inCut;
	for(int e:cut){
		assert(idx.count(e));
		int i=idx[e];
		assert(to[e^1]==E[i][0]&&to[e]==E[i][1]);
		assert(dep[E[i][0]]&&!dep[E[i][1]]);
		assert(cap[e]==0&&cap[e^1]==E[i][2]);
		sum+=cap[e^1];inCut.insert(i);
	}
	assert(sum==f);
	// all S to T edges are listed, and removing them disconnects s, t
	for(int i=0;i<mm;i++)
		if(dep[E[i][0]]&&!dep[E[i][1]])assert(inCut.count(i));
	vector<vector<int>>g(nn+1);
	for(int i=0;i<mm;i++)if(!inCut.count(i))g[E[i][0]].push_back(E[i][1]);
	vector<int>vis(nn+1);vector<int>st={s};vis[s]=1;
	while(!st.empty()){
		int u=st.back();st.pop_back();
		for(int v:g[u])if(!vis[v])vis[v]=1,st.push_back(v);
	}
	assert(!vis[t]);
	checks++;
}
int main(){
	for(int it=0;it<100000;it++)test(rnd(2,8),rnd(0,20),rnd(0,1)?3:100,true);
	for(int it=0;it<300;it++)test(rnd(2,200),rnd(0,2000),1000,false);
	cout<<"checks: "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
