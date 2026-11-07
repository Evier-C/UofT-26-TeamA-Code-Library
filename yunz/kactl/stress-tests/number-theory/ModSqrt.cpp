#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/ModSqrt.h"

bool isP(ll n){
	if(n<2)return 0;
	for(ll i=2;i*i<=n;i++)if(n%i==0)return 0;
	return 1;
}
int main(){
	mt19937_64 rng(5);
	ll checks=0;
	for(ll p=2;p<2000;p++)if(isP(p)){
		vector<int>has(p,0);
		for(ll x=0;x<p;x++)has[x*x%p]=1;
		for(ll n=-3;n<p+3;n++){
			ll nm=(n%p+p)%p,x=cipolla(n,p);
			if(!has[nm])assert(x==-1);
			else assert(x>=0&&x<=p-x&&x*x%p==nm);
			checks++;
		}
	}
	vector<ll>big={1000000007,998244353,(1LL<<61)-1,
		1000000000000000003LL,9223372036854775783LL};
	for(ll p:big)for(int it=0;it<3000;it++){
		ll r=rng()%p,n=(__int128)r*r%p;
		ll x=cipolla(n,p);
		assert(x==min(r,p-r));checks++;
		ll m=rng()%p;
		bool qr=m==0||pw(m,(p-1)/2,p)==1;
		x=cipolla(m,p);
		if(!qr)assert(x==-1);
		else assert(x>=0&&(__int128)x*x%p==m);
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
