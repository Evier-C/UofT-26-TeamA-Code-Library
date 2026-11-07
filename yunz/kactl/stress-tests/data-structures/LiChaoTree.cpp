#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/LiChaoTree.h"

mt19937_64 rng(7);
ll rnd(ll lo,ll hi){return lo+(ll)(rng()%(unsigned long long)(hi-lo+1));}
struct S{ll k,b,x1,x2;};
ll brute(const vector<S>&v,ll x){
	ll r=LLONG_MIN;
	for(auto&s:v)if(s.x1<=x&&x<s.x2)r=max(r,s.k*x+s.b);
	return r;
}

int main(){
	long long checks=0;
	for(int it=0;it<4000;it++){
		bool big=it%10==0;
		ll L=big?rnd(-1000000000,0):rnd(-30,10);
		ll R=L+(big?rnd(1,2000000000):rnd(1,40));
		lc.init(L,R);
		vector<S>v;
		for(int s=0;s<60;s++){
			ll K=big?1000000000:20,B=big?1000000000000000000LL:200;
			ll k=rnd(-K,K),b=rnd(-B,B);
			if(!big&&rng()%3==0)k=rnd(-2,2);
			if(rng()%2){
				lc.addLine({k,b});
				v.push_back({k,b,LLONG_MIN,LLONG_MAX});
			}else{
				ll x1=rnd(L-5,R+5),x2=rnd(L-5,R+5);
				if(x1>x2)swap(x1,x2);
				lc.addSeg({k,b},x1,x2);
				v.push_back({k,b,x1,x2});
			}
			for(int q=0;q<5;q++){
				ll x=rnd(L,R-1);
				assert(lc.query(x)==brute(v,x));checks++;
			}
		}
	}
	// min via negation, many lines on a huge range
	lc.init(-1000000000,1000000001);
	vector<pair<ll,ll>>w;
	for(int i=0;i<200000;i++){
		ll k=rnd(-1000000,1000000),b=rnd(-1000000000000LL,1000000000000LL);
		lc.addLine({-k,-b});w.push_back({k,b});
	}
	for(int q=0;q<300;q++){
		ll x=rnd(-1000000000,1000000000),e=LLONG_MAX;
		for(auto[k,b]:w)e=min(e,k*x+b);
		assert(-lc.query(x)==e);checks++;
	}
	assert(lc.tot<=200000);
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
