#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/ModPow.h"

ll slow(ll a,ll b,ll p){
	ll r=1%p;a=(a%p+p)%p;
	for(;b;b>>=1,a=(__int128)a*a%p)if(b&1)r=(__int128)r*a%p;
	return r;
}
int main(){
	mt19937_64 rng(2);
	ll checks=0;
	for(ll p=1;p<=60;p++)for(ll a=-70;a<=70;a++)for(ll b=0;b<=20;b++){
		ll want=1%p,am=(a%p+p)%p;
		for(int i=0;i<b;i++)want=want*am%p;
		assert(qpow(a,b,p)==want);checks++;
	}
	for(int it=0;it<200000;it++){
		ll p=rng()%3000000000LL+1,a=rng()%(1LL<<62)-(1LL<<61),b=rng()%(1LL<<62);
		assert(qpow(a,b,p)==slow(a,b,p));checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
