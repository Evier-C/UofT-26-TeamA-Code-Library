#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/SqrtIntervals.h"

int main(){
	ll checks=0;
	for(ll n=0;n<=3000;n++){
		ll a=0,b=0;
		for(ll i=1;i<=n;i++)a+=n/i,b+=(n+i-1)/i;
		assert(floorSum(n)==a&&ceilSum(n)==b);checks++;
	}
	mt19937_64 rng(8);
	for(int it=0;it<30;it++){
		ll n=rng()%20000000+1;
		ll a=0,b=0;
		for(ll i=1;i<=n;i++)a+=n/i,b+=(n+i-1)/i;
		assert(floorSum(n)==a&&ceilSum(n)==b);checks++;
	}
	// 大 n: 与另一种算法 2 sum_{i<=s} n/i - s^2 比较
	for(ll n:{1000000000000LL,999999999999LL,123456789012345LL}){
		ll s=sqrtl(n),a=0;
		while(s*s>n)s--;
		while((s+1)*(s+1)<=n)s++;
		for(ll i=1;i<=s;i++)a+=n/i;
		a=2*a-s*s;
		assert(floorSum(n)==a);
		assert(ceilSum(n)==floorSum(n-1)-0+n); // ceil(n/i) = (n-1)/i + 1
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
