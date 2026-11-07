#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/LagrangeInterp.h"

mt19937_64 rng(20);
ll evalp(const vector<ll>&a,ll x){ // 系数 a 在 x 处的值
	x=md(x);
	ll s=0;
	for(int i=(int)a.size()-1;i>=0;i--)
		s=(s*x+a[i])%MOD;
	return s;
}
int main(){
	long long checks=0;
	// Usage 示例
	assert(lagrange({1,2,3},{1,4,9},10)==100);
	assert((lagrangeCoef({1,2,3},{1,4,9})==vector<ll>{0,0,1}));
	checks+=2;
	for(int it=0;it<20000;it++){
		int n=rng()%10+1;
		int deg=rng()%n; // 次数不超过 n-1
		vector<ll> a(n,0);
		for(int i=0;i<=deg;i++)
			a[i]=rng()%MOD;
		// 互不相同的 x (可为负或很大)
		set<ll> used;
		vector<ll> x,y;
		while((int)x.size()<n){
			ll v;
			if(rng()%2)
				v=(ll)(rng()%41)-20;
			else
				v=(ll)(rng()%2000000000000000000ULL)-1000000000000000000LL;
			if(used.count(md(v)))
				continue;
			used.insert(md(v));
			x.push_back(v);
			y.push_back(evalp(a,v));
		}
		ll k=rng()%3?(ll)(rng()%100)-50:(ll)(rng()>>2);
		assert(lagrange(x,y,k)==evalp(a,k));
		assert(lagrangeCoef(x,y)==a);
		// 连续点 0..n-1
		vector<ll> ys(n);
		for(int i=0;i<n;i++)
			ys[i]=evalp(a,i);
		ll k2=rng()%3==0?(ll)(rng()%(n+5)):(ll)(rng()>>1);
		if(rng()%5==0)
			k2=(ll)MOD*(ll)(rng()%5+1)+(ll)(rng()%n); // 模 MOD 落在采样点上
		assert(lagrangeSeq(ys,k2)==evalp(a,k2));
		checks+=3;
	}
	// 自然数幂和 S(m)=1^K+...+m^K
	for(int K=0;K<=12;K++){
		vector<ll> s(K+2);
		for(int j=1;j<=K+1;j++)
			s[j]=(s[j-1]+qpow(j,K))%MOD;
		ll br=0;
		for(int m=1;m<=3000;m++){
			br=(br+qpow(m,K))%MOD;
			if(m%7==0||m<=K+5){
				assert(lagrangeSeq(s,m)==br);
				checks++;
			}
		}
		// 大 m: 与一般版本 (点 1..K+2) 比较; K=1 时有公式
		vector<ll> x(K+2),y(K+2);
		for(int j=0;j<K+2;j++){
			x[j]=j+1;
			y[j]=s[j+1<=K+1?j+1:0];
		}
		y[K+1]=(s[K+1]+qpow(K+2,K))%MOD;
		ll m=1000000000000000000LL+(ll)(rng()%1000);
		assert(lagrangeSeq(s,m)==lagrange(x,y,m));
		if(K==1){
			ll mm=md(m);
			assert(lagrangeSeq(s,m)==mm*md(m+1)%MOD*qpow(2,MOD-2)%MOD);
		}
		checks++;
	}
	// 较大 n: 一般版本与连续版本一致
	{
		int n=2000;
		vector<ll> ys(n),x(n);
		for(int i=0;i<n;i++){
			ys[i]=rng()%MOD;
			x[i]=i;
		}
		for(int t=0;t<3;t++){
			ll k=(ll)(rng()>>1);
			assert(lagrangeSeq(ys,k)==lagrange(x,ys,k));
			checks++;
		}
		vector<ll> a=lagrangeCoef(x,ys);
		for(int t=0;t<20;t++){
			int i=rng()%n;
			assert(evalp(a,i)==ys[i]);
			checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
