#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/ModLog.h"

ll brute(ll a,ll b,ll m,ll c){ // 最小 x 使 c a^x = b, 不存在为 -1
	ll v=c%m;
	for(ll x=0;x<=2*m+5;x++){
		if(v==b%m)return x;
		v=v*(a%m)%m;
	}
	return -1;
}
int main(){
	mt19937_64 rng(3);
	ll checks=0;
	for(ll m=1;m<=130;m++)for(ll a=0;a<m+3;a++)for(ll b=0;b<m+2;b++){
		assert(exbsgs(a,b,m)==brute(a,b,m,1));checks++;
		if(__gcd(a,m)==1){
			ll c=rng()%(m+3);
			assert(bsgs(a,b,m,c)==brute(a,b,m,c));
			assert(bsgs(a,b,m)==brute(a,b,m,1));checks+=2;
		}
	}
	for(ll m=1;m<=500;m++)for(ll a=1;a<m;a++)if(__gcd(a,m)==1){
		ll o=1,v=a%m;while(v!=1%m)v=v*a%m,o++;
		assert(bsgs(a,1,m,a)+1==o);checks++; // 阶
	}
	for(int it=0;it<300;it++){
		ll m=rng()%1000000000+1,a=rng()%m,x=rng()%m;
		ll b=1%m,t=a;
		for(ll e=x;e;e>>=1,t=t*t%m)if(e&1)b=b*t%m;
		ll r=exbsgs(a,b,m);
		assert(r>=0&&r<=x);
		ll v=1%m;t=a;
		for(ll e=r;e;e>>=1,t=t*t%m)if(e&1)v=v*t%m;
		assert(v==b);checks++;
		if(__gcd(a,m)==1)assert(bsgs(a,b,m)==r),checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
