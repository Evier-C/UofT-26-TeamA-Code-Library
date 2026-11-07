#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/WeightedMatching.h"

mt19937 rng(2024);
ll rnd(ll l,ll r){return uniform_int_distribution<ll>(l,r)(rng);}

// brute force: dp over left vertices, mask of used right vertices
ll brute(){
	vector<ll>dp(1<<K.m,LLONG_MAX);dp[0]=0;
	for(int i=1;i<=K.n;i++){
		vector<ll>nd(1<<K.m,LLONG_MAX);
		for(int s=0;s<(1<<K.m);s++)if(dp[s]!=LLONG_MAX)
			for(int j=1;j<=K.m;j++)if(!(s>>(j-1)&1))
				nd[s|1<<(j-1)]=min(nd[s|1<<(j-1)],dp[s]+K.a[i][j]);
		dp=nd;
	}
	return *min_element(dp.begin(),dp.end());
}
long long checks=0;
void check(ll c){ // assignment valid, sums to c, dual certificate
	vector<int>usedR(K.m+1);ll s=0;
	for(int i=1;i<=K.n;i++){
		assert(1<=K.ans[i]&&K.ans[i]<=K.m&&!usedR[K.ans[i]]);
		usedR[K.ans[i]]=1;s+=K.a[i][K.ans[i]];
	}
	assert(s==c);
	ll dual=0;
	for(int i=1;i<=K.n;i++)dual+=K.u[i];
	for(int j=1;j<=K.m;j++)dual+=K.v[j],assert(K.v[j]<=0);
	for(int i=1;i<=K.n;i++)for(int j=1;j<=K.m;j++)assert(K.u[i]+K.v[j]<=K.a[i][j]);
	assert(dual==c);
}
void test(int nn,int mm,ll lo,ll hi,bool br){
	K.n=nn;K.m=mm;
	for(int i=1;i<=K.n;i++)for(int j=1;j<=K.m;j++)K.a[i][j]=rnd(lo,hi);
	ll c=K.km();
	if(br)assert(c==brute());
	check(c);
	checks++;
}
// max weight perfect matching by negation, vs permutations
void testMax(int k){
	K.n=K.m=k;
	vector<vector<ll>>w(k+1,vector<ll>(k+1));
	for(int i=1;i<=k;i++)for(int j=1;j<=k;j++)w[i][j]=rnd(-100,100),K.a[i][j]=-w[i][j];
	ll best=-K.km();
	vector<int>pm(k);iota(pm.begin(),pm.end(),1);
	ll ref=LLONG_MIN;
	do{
		ll s=0;
		for(int i=1;i<=k;i++)s+=w[i][pm[i-1]];
		ref=max(ref,s);
	}while(next_permutation(pm.begin(),pm.end()));
	assert(best==ref);
	ll s=0;
	for(int i=1;i<=k;i++)s+=w[i][K.ans[i]];
	assert(s==best);
	checks++;
}
// max weight matching, vertices may stay unmatched: -max(w,0), pad 0
void testMaxAny(int L,int R){
	vector<vector<ll>>w(L+1,vector<ll>(R+1));
	K.n=K.m=max(L,R);
	for(int i=1;i<=K.n;i++)for(int j=1;j<=K.m;j++)K.a[i][j]=0;
	for(int i=1;i<=L;i++)for(int j=1;j<=R;j++){
		w[i][j]=rnd(-50,50);K.a[i][j]=-max(w[i][j],0LL);
	}
	ll best=-K.km();
	// brute: dp over left, each left may skip
	vector<ll>dp(1<<R,LLONG_MIN);dp[0]=0;
	for(int i=1;i<=L;i++){
		vector<ll>nd=dp;
		for(int s=0;s<(1<<R);s++)if(dp[s]!=LLONG_MIN)
			for(int j=1;j<=R;j++)if(!(s>>(j-1)&1))
				nd[s|1<<(j-1)]=max(nd[s|1<<(j-1)],dp[s]+w[i][j]);
		dp=nd;
	}
	assert(best==*max_element(dp.begin(),dp.end()));
	checks++;
}
// missing edges with cost 1e12, compare with brute
void testMissing(){
	K.n=rnd(1,6);K.m=rnd(K.n,7);
	for(int i=1;i<=K.n;i++)for(int j=1;j<=K.m;j++)
		K.a[i][j]=rnd(0,2)?rnd(-1000,1000):(ll)1e12;
	ll c=K.km();
	assert(c==brute());
	check(c);
	checks++;
}
int main(){
	for(int it=0;it<10000;it++)testMissing();
	for(int it=0;it<5000;it++)testMaxAny(rnd(1,7),rnd(1,7));
	for(int it=0;it<30000;it++){
		int nn=rnd(1,7),mm=rnd(nn,8);
		test(nn,mm,rnd(0,1)?-10:-1000000000,rnd(0,1)?10:1000000000,true);
	}
	for(int it=0;it<5000;it++)testMax(rnd(1,7));
	for(int it=0;it<200;it++){
		int nn=rnd(1,100),mm=rnd(nn,120);
		test(nn,mm,-1000000,1000000,false);
	}
	test(500,500,0,1000000000,false);
	test(300,500,-1000000000,1000000000,false);
	cout<<"checks: "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
