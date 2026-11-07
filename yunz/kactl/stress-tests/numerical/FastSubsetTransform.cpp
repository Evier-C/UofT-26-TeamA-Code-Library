#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/FastSubsetTransform.h"

mt19937 rng(16);
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
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
