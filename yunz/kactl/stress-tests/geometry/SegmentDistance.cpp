#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/SegmentDistance.h"

typedef long double ld;
mt19937 rng(3);
double rr(double lo,double hi){return uniform_real_distribution<double>(lo,hi)(rng);}

// brute: ternary search on the parameter of the segment
ld brute(Point s,Point e,Point p){
	auto f=[&](ld t){return hypotl(s.x+(e.x-s.x)*t-p.x,s.y+(e.y-s.y)*t-p.y);};
	ld lo=0,hi=1;
	for(int i=0;i<100;i++){
		ld m1=(2*lo+hi)/3,m2=(lo+2*hi)/3;
		if(f(m1)<f(m2))hi=m2;else lo=m1;
	}
	return min({f(lo),f(0),f(1)});
}
int main(){
	ll checks=0;
	for(int it=0;it<150000;it++){
		Point s,e,p;
		if(it%2){
			int L=it%4==1?3:20;
			auto g=[&](){return Point((int)(rng()%(2*L+1))-L,(int)(rng()%(2*L+1))-L);};
			s=g();e=g();p=g();
		}else{
			s=Point(rr(-100,100),rr(-100,100));e=Point(rr(-100,100),rr(-100,100));
			p=Point(rr(-100,100),rr(-100,100));
		}
		double d=segDist(s,e,p);
		assert(fabsl(d-brute(s,e,p))<1e-7);
		checks++;
	}
	// the usage example
	assert(segDist(Point(0,0),Point(2,2),Point(1,1))<1e-9);
	cout<<"Tests passed! ("<<checks+1<<" checks)"<<endl;
}
