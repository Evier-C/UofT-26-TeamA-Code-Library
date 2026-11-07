#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/sideOf.h"

mt19937 rng(6);
double rr(double lo,double hi){return uniform_real_distribution<double>(lo,hi)(rng);}
int main(){
	ll checks=0;
	for(int t=0;t<1000000;t++){
		const int G=t%2?5:1000;
		auto g=[&](){return Point((int)(rng()%(2*G+1))-G,(int)(rng()%(2*G+1))-G);};
		Point s=g(),e=g(),p=g();
		ll cr=(ll)(e.x-s.x)*(ll)(p.y-s.y)-(ll)(e.y-s.y)*(ll)(p.x-s.x);
		assert(sideOf(s,e,p)==(cr>0)-(cr<0));
		checks++;
		if(s==e)continue;
		double lim=rr(0,3);
		long double dx=e.x-s.x,dy=e.y-s.y,d=cr/hypotl(dx,dy);
		if(fabsl(fabsl(d)-lim)<1e-9)continue;
		int want=fabsl(d)<=lim?0:(d>0?1:-1);
		assert(sideOf(s,e,p,lim)==want);
		checks++;
	}
	// usage example
	assert(sideOf(Point(0,0),Point(1,0),Point(5,1))==1);
	assert(sideOf(Point(0,0),Point(1,0),Point(5,1e-7),1e-6)==0);
	cout<<"Tests passed! ("<<checks+2<<" checks)"<<endl;
}
