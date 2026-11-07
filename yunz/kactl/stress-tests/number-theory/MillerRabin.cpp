#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/MillerRabin.h"

bool slowPrime(ll n){
	if(n<2)return 0;
	for(ll i=2;i*i<=n;i++)if(n%i==0)return 0;
	return 1;
}
int main(){
	mt19937_64 rng(6);
	ll checks=0;
	int L=2000000;
	vector<bool>comp(L+1);
	comp[0]=comp[1]=1;
	for(int i=2;i<=L;i++)if(!comp[i])
		for(ll j=(ll)i*i;j<=L;j+=i)comp[j]=1;
	for(int i=-10;i<=L;i++)
		assert(isPrime(i)==(i>=0&&!comp[i])),checks++;
	for(int it=0;it<3000;it++){
		ll n=rng()%1000000000000LL;
		assert(isPrime(n)==slowPrime(n));checks++;
	}
	// 已知的大质数和强伪素数
	for(ll p:{1000000007LL,998244353LL,(1LL<<61)-1,
		1000000000000000003LL,9223372036854775783LL})
		assert(isPrime(p)),checks++;
	for(ll c:{3215031751LL,3825123056546413051LL,
		(1LL<<61)-3,561LL,41041LL,825265LL,9223372036854775807LL})
		if(c>0&&c<1000000000000LL)assert(isPrime(c)==slowPrime(c)),checks++;
	assert(!isPrime(3215031751LL)&&!isPrime(3825123056546413051LL));
	assert(!isPrime(9223372036854775807LL)); // 7 * ...
	// 两个大质数的乘积
	vector<ll>ps;
	while(ps.size()<200){
		ll x=rng()%2000000000+1000000000;
		if(slowPrime(x))ps.push_back(x);
	}
	for(int i=0;i<200;i++)for(int j=i;j<200;j++)
		if((__int128)ps[i]*ps[j]<=LLONG_MAX)
			assert(!isPrime(ps[i]*ps[j])),checks++;
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
