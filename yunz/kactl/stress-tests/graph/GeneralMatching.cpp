#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/GeneralMatching.h"
Blossom BM2; // second global instance

mt19937 rng(31337);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}

// brute force: bitmask dp, f[S] = max matching inside vertex set S
int brute(int nn,vector<vector<int>>&adj){
	vector<int>f(1<<nn,0);
	for(int s=1;s<(1<<nn);s++){
		int i=__builtin_ctz(s),r=s^(1<<i);
		f[s]=f[r];
		for(int j=0;j<nn;j++)if((r>>j&1)&&adj[i+1][j+1])
			f[s]=max(f[s],f[r^(1<<j)]+1);
	}
	return f[(1<<nn)-1];
}
// independent check: rank of random Tutte matrix mod p is 2 * matching
const ll P=1000000007;
ll pw(ll b,ll e){ll r=1;b%=P;for(;e;e>>=1,b=b*b%P)if(e&1)r=r*b%P;return r;}
int tutte(int nn,vector<pair<int,int>>&ed){
	vector<vector<ll>>A(nn,vector<ll>(nn,0));
	for(auto [u,v]:ed)if(u!=v){
		ll r=rng()%(P-1)+1;
		A[u-1][v-1]=(A[u-1][v-1]+r)%P;A[v-1][u-1]=(A[v-1][u-1]+P-r)%P;
	}
	int rk=0;
	for(int c=0;c<nn&&rk<nn;c++){
		int piv=-1;
		for(int i=rk;i<nn;i++)if(A[i][c]){piv=i;break;}
		if(piv<0)continue;
		swap(A[piv],A[rk]);
		ll inv=pw(A[rk][c],P-2);
		for(int i=0;i<nn;i++)if(i!=rk&&A[i][c]){
			ll f=A[i][c]*inv%P;
			for(int j=c;j<nn;j++)A[i][j]=(A[i][j]-f*A[rk][j]%P+P)%P;
		}
		rk++;
	}
	return rk/2;
}
long long checks=0;
void test(int nn,int ne,int mode){
	BM.init(nn);
	vector<vector<int>>adj(nn+1,vector<int>(nn+1,0));
	vector<pair<int,int>>ed;
	for(int k=0;k<ne;k++){
		int u=rnd(1,nn),v=rnd(1,nn);
		BM.add(u,v);adj[u][v]=adj[v][u]=1;ed.push_back({u,v});
	}
	int res=BM.solve();
	BM2.init(nn);
	for(auto [u,v]:ed)BM2.add(u,v);
	assert(BM2.solve()==res);
	if(mode==0)assert(res==brute(nn,adj));
	if(mode==1)assert(res==tutte(nn,ed));
	int got=0;
	for(int u=1;u<=nn;u++)if(BM.mt[u]){
		int v=BM.mt[u];
		assert(v!=u&&adj[u][v]&&BM.mt[v]==u);
		if(v>u)got++;
	}
	assert(got==res);
	checks++;
}
int main(){
	for(int it=0;it<50000;it++){
		int nn=rnd(1,12);
		test(nn,rnd(0,nn*(nn-1)/2+2),0);
	}
	for(int it=0;it<20000;it++){
		int nn=rnd(1,8);
		test(nn,rnd(0,nn+3),0); // sparse: many odd cycles, unmatched
	}
	for(int it=0;it<200;it++){
		int nn=rnd(1,80);
		test(nn,rnd(0,3*nn),1);
	}
	for(int it=0;it<5;it++)test(1000,rnd(1000,99000),2);
	// odd cycles chained: triangles sharing vertices
	BM.init(999);
	for(int i=1;i+2<=999;i+=2)BM.add(i,i+1),BM.add(i+1,i+2),BM.add(i,i+2);
	assert(BM.solve()==499);checks++;
	cout<<"checks: "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
