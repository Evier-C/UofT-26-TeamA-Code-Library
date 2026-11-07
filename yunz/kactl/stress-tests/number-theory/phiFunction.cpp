#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/phiFunction.h"

int main(){
	mt19937_64 rng(11);
	ll checks=0;
	for(ll n=1;n<=3000;n++){
		ll c=0;
		for(ll k=1;k<=n;k++)c+=__gcd(k,n)==1;
		assert(getPhi(n)==c);checks++;
	}
	for(int it=0;it<300;it++){ // sum_{d | n} phi(d) = n
		ll n=rng()%1000000000000LL+1,s=0;
		for(ll d=1;d*d<=n;d++)if(n%d==0){
			s+=getPhi(d);
			if(d*d!=n)s+=getPhi(n/d);
		}
		assert(s==n);checks++;
	}
	assert(getPhi(1000000007)==1000000006);
	assert(getPhi(1LL<<40)==1LL<<39);
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
