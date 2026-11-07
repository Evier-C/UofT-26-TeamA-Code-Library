#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/euclid.h"

int main(){
	mt19937_64 rng(9);
	ll checks=0;
	for(ll a=0;a<=300;a++)for(ll b=0;b<=300;b++){
		if(!a&&!b)continue;
		ll x,y,g=exgcd(a,b,x,y);
		assert(g==__gcd(a,b)&&a*x+b*y==g);
		assert(abs(x)<=max(b,1LL)&&abs(y)<=max(a,1LL));
		checks++;
	}
	for(int it=0;it<1000000;it++){
		ll a=rng()%LLONG_MAX+1,b=rng()%LLONG_MAX+1;
		if(it&1)b=rng()%1000000+1;
		ll x,y,g=exgcd(a,b,x,y);
		assert(g==__gcd(a,b));
		assert((__int128)a*x+(__int128)b*y==g);
		checks++;
	}
	for(ll m:{1000000007LL,998244353LL,1000000LL})for(int it=0;it<10000;it++){
		ll a=rng()%m;if(__gcd(a,m)!=1)continue;
		ll x,y;exgcd(a,m,x,y);
		ll iv=(x%m+m)%m;
		assert(a*iv%m==1);checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
