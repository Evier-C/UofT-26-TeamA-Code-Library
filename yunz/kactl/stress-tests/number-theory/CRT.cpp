#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/CRT.h"

ll a[20],m[20];
int main(){
	mt19937_64 rng(10);
	ll checks=0;
	for(int it=0;it<200000;it++){
		int n=rng()%4+1;
		for(int i=1;i<=n;i++)m[i]=rng()%12+1,a[i]=(ll)(rng()%40)-20;
		ll L=1;
		for(int i=1;i<=n;i++)L=L/__gcd(L,m[i])*m[i];
		ll want=-1;
		for(ll x=0;x<L&&want<0;x++){
			bool ok=1;
			for(int i=1;i<=n;i++)ok&=((x-a[i])%m[i]+m[i])%m[i]==0;
			if(ok)want=x;
		}
		assert(excrt(a,m,n)==want);checks++;
		bool cop=1;
		for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)cop&=__gcd(m[i],m[j])==1;
		if(cop)assert(crt(a,m,n)==want),checks++;
	}
	// 大模数: 乘积接近 1e18
	vector<ll>P={1000000007,998244353,7};
	for(int it=0;it<100000;it++){
		int n=3;
		for(int i=1;i<=n;i++)m[i]=P[i-1],a[i]=rng()%m[i];
		ll x=crt(a,m,n),y=excrt(a,m,n);
		assert(x==y&&x>=0);
		assert((__int128)x<(__int128)P[0]*P[1]*P[2]);
		for(int i=1;i<=n;i++)assert(x%m[i]==a[i]);
		checks++;
	}
	for(int it=0;it<100000;it++){ // 不互质的大模数
		int n=rng()%5+1;
		ll x0=rng()%1000000000000000000LL;
		ll L=1;bool big=0;
		for(int i=1;i<=n;i++){
			m[i]=rng()%1000000000+1;
			if(it&1)m[i]=m[i]/1000*1000+1000; // 公因子多
			__int128 nl=(__int128)L/__gcd(L,m[i])*m[i];
			if(nl>(__int128)4e18){big=1;break;}
			L=nl;a[i]=x0%m[i];
		}
		if(big)continue;
		ll y=excrt(a,m,n);
		assert(y==x0%L);checks++;
		if(n>=2){ // 改一个余数, 通常无解
			a[1]=(a[1]+1)%m[1];
			ll z=excrt(a,m,n);
			if(z>=0)for(int i=1;i<=n;i++)assert(z%m[i]==a[i]);
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
