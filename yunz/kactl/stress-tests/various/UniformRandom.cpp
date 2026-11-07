#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/various/UniformRandom.h"

int main(){
	ll checks=0;
	vector<int>cnt(10);
	for(int i=0;i<1000000;i++){
		ll x=rnd(1,10);
		assert(x>=1&&x<=10);
		cnt[x-1]++;checks++;
	}
	for(int c:cnt)assert(c>95000&&c<105000);
	for(int i=0;i<100000;i++){
		ll l=(ll)(rng()>>1)-(1LL<<62),r=l+(ll)(rng()>>2);
		ll x=rnd(l,r);
		assert(l<=x&&x<=r);checks++;
	}
	assert(rnd(5,5)==5);
	ll x=rnd(LLONG_MIN,LLONG_MAX);(void)x;
	int a[11];
	for(int i=1;i<=10;i++)a[i]=i;
	shuffle(a+1,a+11,rng);
	sort(a+1,a+11);
	for(int i=1;i<=10;i++)assert(a[i]==i);
	double y=uniform_real_distribution<double>(0,1)(rng);
	assert(y>=0&&y<1);
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
