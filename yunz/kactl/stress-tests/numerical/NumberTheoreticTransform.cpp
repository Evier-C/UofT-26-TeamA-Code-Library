#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/NumberTheoreticTransform.h"

mt19937 rng(15);
int main(){
	long long checks=0;
	assert((nttConv({1,2},{1,3})==vector<ll>{1,5,6}));
	assert(nttConv({},{1}).empty());
	checks+=2;
	for(int it=0;it<20000;it++){
		int n=rng()%50+1,m=rng()%50+1;
		vector<ll> a(n),b(m);
		for(auto&v:a)v=rng()%2?rng()%MOD:MOD-1;
		for(auto&v:b)v=rng()%2?rng()%MOD:MOD-1;
		vector<ll> c(n+m-1);
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)
			c[i+j]=(c[i+j]+a[i]*b[j])%MOD;
		assert(nttConv(a,b)==c);
		checks++;
	}
	// 正变换: 与定义 f(w^k) 比较
	for(int it=0;it<50;it++){
		int n=1<<(rng()%7);
		vector<ll> f(n),g;
		for(auto&v:f)v=rng()%MOD;
		g=f;ntt(g,1);
		ll w=qpow(G,(MOD-1)/n);
		for(int k=0;k<n;k++){
			ll s=0,x=qpow(w,k),p=1;
			for(int i=0;i<n;i++)s=(s+f[i]*p)%MOD,p=p*x%MOD;
			assert(g[k]==s);
			checks++;
		}
		ntt(g,-1);
		assert(g==f);
	}
	// 大规模: 长度 2^21, 抽查
	{
		int n=1000000,m=1000000;
		vector<ll> a(n),b(m);
		for(auto&v:a)v=rng()%MOD;
		for(auto&v:b)v=rng()%MOD;
		vector<ll> c=nttConv(a,b);
		assert((int)c.size()==n+m-1);
		for(int t=0;t<30;t++){
			int k=rng()%(n+m-1);
			ll s=0;
			for(int i=max(0,k-m+1);i<=min(k,n-1);i++)s=(s+a[i]*b[k-i])%MOD;
			assert(c[k]==s);
			checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
