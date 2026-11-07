#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/MaxPlusConvolution.h"

mt19937 rng(17);
vector<ll> concave(int m,ll R){ // 差分不增
	vector<ll> d(m-1>0?m-1:0);
	for(auto&v:d)v=(ll)(rng()%(2*R+1))-R;
	sort(d.rbegin(),d.rend());
	if(rng()%3==0)for(auto&v:d)v=d.empty()?0:d[0]; // 线性, 大量相等
	vector<ll> b(m);
	b[0]=(ll)(rng()%(2*R+1))-R;
	for(int i=1;i<m;i++)b[i]=b[i-1]+d[i-1];
	return b;
}
vector<ll> brute(const vector<ll>&a,const vector<ll>&b){
	int n=a.size(),m=b.size();
	vector<ll> c(n+m-1,LLONG_MIN);
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)c[i+j]=max(c[i+j],a[i]+b[j]);
	return c;
}
int main(){
	long long checks=0;
	assert((maxPlus({1,5,2},{0,3,4})==vector<ll>{1,5,8,9,6})); // Usage
	checks++;
	for(int it=0;it<50000;it++){
		int n=rng()%12+1,m=rng()%12+1;
		ll R=rng()%2?3:1000000000;
		vector<ll> a(n);
		for(auto&v:a)v=(ll)(rng()%(2*R+1))-R;
		vector<ll> b=concave(m,R);
		assert(maxPlus(a,b)==brute(a,b));
		checks++;
	}
	for(int it=0;it<20;it++){
		int n=rng()%3000+1,m=rng()%3000+1;
		vector<ll> a(n);
		for(auto&v:a)v=(ll)(rng()%2000001)-1000000;
		vector<ll> b=concave(m,1000);
		assert(maxPlus(a,b)==brute(a,b));
		checks++;
	}
	// 大规模只测速度与长度
	{
		int n=500000,m=500000;
		vector<ll> a(n);
		for(auto&v:a)v=(ll)(rng()%2000001)-1000000;
		vector<ll> b=concave(m,1000);
		vector<ll> c=maxPlus(a,b);
		assert((int)c.size()==n+m-1);
		for(int t=0;t<20;t++){
			int k=rng()%(n+m-1);
			ll s=LLONG_MIN;
			for(int i=max(0,k-m+1);i<=min(k,n-1);i++)s=max(s,a[i]+b[k-i]);
			assert(c[k]==s);
			checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
