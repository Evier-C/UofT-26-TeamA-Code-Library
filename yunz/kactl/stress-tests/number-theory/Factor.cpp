#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/Factor.h"

vector<ll>trial(ll n){
	vector<ll>f;
	for(ll i=2;i*i<=n;i++)while(n%i==0)f.push_back(i),n/=i;
	if(n>1)f.push_back(n);
	return f;
}
void check(ll n,ll&checks){
	vector<ll>f;factor(n,f);
	sort(f.begin(),f.end());
	__int128 pr=1;
	for(ll x:f)assert(isPrime(x)),pr*=x;
	assert(pr==n);checks++;
}
int main(){
	mt19937_64 rng(7);
	ll checks=0;
	for(ll n=1;n<=100000;n++){
		vector<ll>f;factor(n,f);
		sort(f.begin(),f.end());
		assert(f==trial(n));checks++;
	}
	{vector<ll>f;factor(2299,f);sort(f.begin(),f.end());
	assert((f==vector<ll>{11,11,19}));}
	for(int it=0;it<2000;it++){
		ll n=rng()%1000000000000LL+1;
		vector<ll>f;factor(n,f);
		sort(f.begin(),f.end());
		assert(f==trial(n));checks++;
	}
	for(int it=0;it<3000;it++)check(rng()%LLONG_MAX+1,checks);
	vector<ll>ps;
	while(ps.size()<60){
		ll x=rng()%2000000000+1000000000;
		if(isPrime(x))ps.push_back(x);
	}
	for(int i=0;i<60;i++)for(int j=i;j<60;j++){
		ll n=ps[i]*ps[j];
		check(n,checks);
		vector<ll>f;factor(n,f);
		assert(f.size()==2);
	}
	for(ll n:{4LL,8LL,1LL<<62,(1LL<<61)-1,9223372036854775783LL,
		9223372036854775807LL,999999999999999989LL})
		check(n,checks);
	check(1LL*1000003*1000003*1000003,checks);
	check(1LL*ps[0]*ps[0],checks);
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
