#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/HopcroftKarp.h"

mt19937 rng(99);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}

// brute force: dp over left vertices with mask of used right vertices
int brute(int nn,int mm,vector<pair<int,int>>&ed){
	vector<int>dp(1<<mm,-1);dp[0]=0;
	for(int i=1;i<=nn;i++){
		vector<int>nd=dp;
		for(int s=0;s<(1<<mm);s++)if(dp[s]>=0)
			for(auto [a,b]:ed)if(a==i&&!(s>>(b-1)&1))
				nd[s|1<<(b-1)]=max(nd[s|1<<(b-1)],dp[s]+1);
		dp=nd;
	}
	return *max_element(dp.begin(),dp.end());
}
// simple Kuhn for larger cases
int kuhnMatch[N];bool kv[N];
bool kuhn(int u){
	for(int v:g[u])if(!kv[v]){
		kv[v]=1;
		if(!kuhnMatch[v]||kuhn(kuhnMatch[v])){kuhnMatch[v]=u;return true;}
	}
	return false;
}
long long checks=0;
void test(int nn,int mm,int ne,int mode){
	init(nn,mm);
	vector<pair<int,int>>ed;set<pair<int,int>>es;
	for(int k=0;k<ne;k++){
		int a=rnd(1,nn),b=rnd(1,mm);
		ed.push_back({a,b});es.insert({a,b});g[a].push_back(b);
	}
	int res=hk();
	int ref;
	if(mode==0)ref=brute(nn,mm,ed);
	else{
		for(int j=1;j<=mm;j++)kuhnMatch[j]=0;
		ref=0;
		for(int i=1;i<=nn;i++){
			for(int j=1;j<=mm;j++)kv[j]=0;
			ref+=kuhn(i);
		}
	}
	assert(res==ref);
	int got=0;
	for(int u=1;u<=nn;u++)if(mL[u]){
		assert(es.count({u,mL[u]}));
		assert(mR[mL[u]]==u);got++;
	}
	for(int v=1;v<=mm;v++)if(mR[v])assert(mL[mR[v]]==v);
	assert(got==res);
	checks++;
}
int main(){
	for(int it=0;it<50000;it++)test(rnd(1,8),rnd(1,8),rnd(0,20),0);
	for(int it=0;it<500;it++)test(rnd(1,200),rnd(1,200),rnd(0,800),1);
	for(int it=0;it<3;it++)test(1000,1000,rnd(1000,20000),1);
	// long augmenting paths: chain-like graph
	init(100000,100000);
	for(int i=1;i<=100000;i++){
		if(i>1)g[i].push_back(i-1);
		g[i].push_back(i);
	}
	assert(hk()==100000);checks++;
	cout<<"checks: "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
