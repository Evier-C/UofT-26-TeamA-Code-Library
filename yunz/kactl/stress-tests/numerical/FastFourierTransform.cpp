#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/FastFourierTransform.h"

mt19937 rng(13);
vector<ll> brute(const vector<ll>&a,const vector<ll>&b){
	if(a.empty()||b.empty())return {};
	vector<ll> c(a.size()+b.size()-1);
	for(int i=0;i<(int)a.size();i++)
		for(int j=0;j<(int)b.size();j++)c[i+j]+=a[i]*b[j];
	return c;
}
int main(){
	long long checks=0;
	assert((conv({1,2},{1,3})==vector<ll>{1,5,6}));
	assert(conv({},{1}).empty());
	checks+=2;
	for(int it=0;it<20000;it++){
		int n=rng()%40+1,m=rng()%40+1;
		ll R=rng()%2?10:1000000;
		vector<ll> a(n),b(m);
		for(auto&v:a)v=(ll)(rng()%(2*R+1))-R;
		for(auto&v:b)v=(ll)(rng()%(2*R+1))-R;
		assert(conv(a,b)==brute(a,b));
		checks++;
	}
	// 直接用 fft: 正变换后逆变换得到原数组
	for(int it=0;it<100;it++){
		int n=1<<(rng()%12);
		vector<cp> f(n),g;
		for(auto&z:f)z={(double)(rng()%100),(double)(rng()%100)};
		g=f;
		fft(g,1);fft(g,-1);
		for(int i=0;i<n;i++)
			assert(fabs(f[i].x-g[i].x)<1e-6&&fabs(f[i].y-g[i].y)<1e-6);
		checks++;
	}
	// 较大: 结果约 1e13 (6e3 * 5e3 * 4e5)
	for(int it=0;it<3;it++){
		int n=200000+rng()%1000,m=200000+rng()%1000;
		vector<ll> a(n),b(m);
		for(auto&v:a)v=rng()%5000;
		for(auto&v:b)v=rng()%5000;
		vector<ll> c=conv(a,b);
		assert((int)c.size()==n+m-1);
		for(int t=0;t<300;t++){
			int k=rng()%(n+m-1);
			ll s=0;
			for(int i=max(0,k-m+1);i<=min(k,n-1);i++)s+=a[i]*b[k-i];
			assert(c[k]==s);
			checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
