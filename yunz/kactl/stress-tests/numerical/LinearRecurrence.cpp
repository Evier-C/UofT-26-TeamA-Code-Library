#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/LinearRecurrence.h"

mt19937 rng(4);
int main(){
	long long checks=0;
	// Fibonacci
	{
		vector<ll> f(100);
		f[0]=0;f[1]=1;
		for(int i=2;i<100;i++)f[i]=(f[i-1]+f[i-2])%MOD;
		for(int k=0;k<100;k++)assert(linearRec({0,1},{1,1},k)==f[k]);
		checks+=100;
	}
	assert(linearRec({},{},5)==0);
	for(int it=0;it<3000;it++){
		int n=rng()%7+1;
		vector<ll> S(n),tr(n);
		for(auto&v:S)v=rng()%MOD;
		for(auto&v:tr)v=(rng()%2)?rng()%MOD:rng()%3;
		int K=200;
		vector<ll> s(K);
		for(int i=0;i<K;i++){
			if(i<n)s[i]=S[i];
			else{
				s[i]=0;
				for(int j=0;j<n;j++)s[i]=(s[i]+tr[j]*s[i-j-1])%MOD;
			}
		}
		for(int t=0;t<5;t++){
			int k=rng()%K;
			assert(linearRec(S,tr,k)==s[k]);
			checks++;
		}
		// 配合 BM 使用
		vector<ll> C=BM(vector<ll>(s.begin(),s.begin()+2*n));
		int k=rng()%K;
		assert(linearRec(s,C,k)==s[k]);
		checks++;
	}
	// 大 k: 与矩阵快速幂比较
	for(int it=0;it<200;it++){
		int n=rng()%4+1;
		vector<ll> S(n),tr(n);
		for(auto&v:S)v=rng()%MOD;
		for(auto&v:tr)v=rng()%MOD;
		ll k=((ll)rng()<<20)^rng();
		// 状态 (s[i+n-1],...,s[i]), 转移矩阵 T
		vector<vector<ll>> T(n,vector<ll>(n)),R(n,vector<ll>(n));
		for(int j=0;j<n;j++)T[0][j]=tr[j];
		for(int i=1;i<n;i++)T[i][i-1]=1;
		for(int i=0;i<n;i++)R[i][i]=1;
		auto mul=[&](vector<vector<ll>>&X,vector<vector<ll>>&Y){
			vector<vector<ll>> Z(n,vector<ll>(n));
			for(int i=0;i<n;i++)for(int l=0;l<n;l++)for(int j=0;j<n;j++)
				Z[i][j]=(Z[i][j]+X[i][l]*Y[l][j])%MOD;
			return Z;
		};
		for(ll e=k;e;e>>=1){if(e&1)R=mul(R,T);T=mul(T,T);}
		// 状态向量 v0=(S[n-1],...,S[0]); R*v0 的最后一项为 s[k]
		ll want=0;
		for(int j=0;j<n;j++)want=(want+R[n-1][j]*S[n-1-j])%MOD;
		assert(linearRec(S,tr,k)==want);
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
