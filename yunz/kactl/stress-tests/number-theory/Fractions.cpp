#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/Fractions.h"

void ok(Frac f,__int128 p,__int128 q){ // f 等于 p/q
	assert(f.q>0&&gcd(f.p,f.q)==1);
	assert((__int128)f.p*q==p*f.q);
}
int main(){
	mt19937_64 rng(12);
	ll checks=0;
	Frac c=mk(1,2)+mk(1,3);
	assert(c.p==5&&c.q==6);
	for(int it=0;it<1000000;it++){
		ll ap=(ll)(rng()%2001)-1000,aq=(ll)(rng()%2001)-1000;
		ll bp=(ll)(rng()%2001)-1000,bq=(ll)(rng()%2001)-1000;
		if(!aq||!bq)continue;
		Frac a=mk(ap,aq),b=mk(bp,bq);
		ok(a,ap,aq),ok(b,bp,bq);
		ok(a+b,(__int128)ap*bq+(__int128)bp*aq,(__int128)aq*bq);
		ok(a-b,(__int128)ap*bq-(__int128)bp*aq,(__int128)aq*bq);
		ok(a*b,(__int128)ap*bp,(__int128)aq*bq);
		if(bp)ok(a/b,(__int128)ap*bq,(__int128)aq*bp);
		long double x=(long double)ap/aq,y=(long double)bp/bq;
		bool eq=(__int128)ap*bq==(__int128)bp*aq;
		assert((a==b)==eq);
		if(!eq)assert((a<b)==(x<y));
		else assert(!(a<b)&&!(b<a));
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
