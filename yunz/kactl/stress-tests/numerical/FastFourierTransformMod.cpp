#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/FastFourierTransformMod.h"

mt19937 rng(14);
ll pw(ll b,ll e){ll r=1;for(b%=MOD;e;e>>=1,b=b*b%MOD)if(e&1)r=r*b%MOD;return r;}
ll evalp(const vector<ll>&a,ll x){
	ll s=0;
	for(int i=(int)a.size()-1;i>=0;i--)s=(s*x+a[i])%MOD;
	return s;
}
int main(){
	long long checks=0;
	for(int it=0;it<20000;it++){
		int n=rng()%40+1,m=rng()%40+1;
		vector<ll> a(n),b(m);
		bool big=rng()%2;
		for(auto&v:a)v=big?rng()%MOD:MOD-1-rng()%3;
		for(auto&v:b)v=big?rng()%MOD:MOD-1-rng()%3;
		vector<ll> c(n+m-1);
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)
			c[i+j]=(c[i+j]+a[i]*b[j])%MOD;
		assert(convMod(a,b)==c);
		checks++;
	}
	assert(convMod({},{1}).empty());
	// 大规模: 在随机点处比较 a(x)b(x) 与 c(x), 并抽查若干项
	for(int it=0;it<4;it++){
		int n=(it<2?500000:100000)+rng()%1000,m=n-rng()%1000;
		vector<ll> a(n),b(m);
		for(auto&v:a)v=it%2?MOD-1:rng()%MOD;
		for(auto&v:b)v=it%2?MOD-1:rng()%MOD;
		vector<ll> c=convMod(a,b);
		assert((int)c.size()==n+m-1);
		for(int t=0;t<5;t++){
			ll x=rng()%MOD;
			assert(evalp(a,x)*evalp(b,x)%MOD==evalp(c,x));
			checks++;
		}
		for(int t=0;t<20;t++){
			int k=rng()%(n+m-1);
			ll s=0;
			for(int i=max(0,k-m+1);i<=min(k,n-1);i++)s=(s+a[i]*b[k-i])%MOD;
			assert(c[k]==s);
			checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
