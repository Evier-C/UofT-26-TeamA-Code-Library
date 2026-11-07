#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/FWT.h"

mt19937 rng(18);
int main(){
	long long checks=0;
	for(int it=0;it<3000;it++){
		int k=rng()%9,n=1<<k;
		vector<ll> a(n),b(n);
		for(auto&v:a)v=(ll)(rng()%2001)-1000;
		for(auto&v:b)v=(ll)(rng()%2001)-1000;
		for(int op=0;op<3;op++){
			vector<ll> want(n,0);
			for(int i=0;i<n;i++)for(int j=0;j<n;j++){
				int z=op==0?(i|j):op==1?(i&j):(i^j);
				want[z]+=a[i]*b[j];
			}
			vector<ll> x=a,y=b;
			void(*F)(vector<ll>&,int)=op==0?fwtOr:op==1?fwtAnd:fwtXor;
			F(x,1);F(y,1);
			for(int i=0;i<n;i++)x[i]*=y[i];
			F(x,-1);
			assert(x==want);
			// 逆变换还原
			vector<ll> z=a;F(z,1);F(z,-1);
			assert(z==a);
			checks+=2;
		}
		// or 正变换为子集和
		vector<ll> s=a;fwtOr(s,1);
		for(int m=0;m<n;m++){
			ll t=0;
			for(int i=0;i<n;i++)if((i&m)==i)t+=a[i];
			assert(s[m]==t);
		}
		checks++;
		// 三个卷积函数 (Usage 里的 API)
		vector<ll> wo(n,0),wa(n,0),wx(n,0);
		for(int i=0;i<n;i++)for(int j=0;j<n;j++){
			wo[i|j]+=a[i]*b[j];wa[i&j]+=a[i]*b[j];wx[i^j]+=a[i]*b[j];
		}
		assert(orConv(a,b)==wo&&andConv(a,b)==wa&&xorConv(a,b)==wx);
		checks+=3;
	}
	// 较大: 2^17, 抽查
	{
		int n=1<<17;
		vector<ll> a(n),b(n);
		for(auto&v:a)v=rng()%1000;
		for(auto&v:b)v=rng()%1000;
		vector<ll> c=xorConv(a,b),d=orConv(a,b),e=andConv(a,b);
		for(int t=0;t<5;t++){
			int k=rng()%n;
			ll s1=0,s2=0,s3=0;
			for(int i=0;i<n;i++)s1+=a[i]*b[i^k];
			// or: i, j 都是 k 的子集; and: 都是 k 的超集
			int u=n-1-k;
			for(int i=k;;i=(i-1)&k){
				for(int j=k;;j=(j-1)&k){
					if((i|j)==k)s2+=a[i]*b[j];
					if(j==0)break;
				}
				if(i==0)break;
			}
			for(int i=u;;i=(i-1)&u){
				for(int j=u;;j=(j-1)&u){
					if((i&j)==0)s3+=a[i|k]*b[j|k];
					if(j==0)break;
				}
				if(i==0)break;
			}
			assert(c[k]==s1&&d[k]==s2&&e[k]==s3);
			checks+=3;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
