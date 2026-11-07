#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/OnSegment.h"

mt19937 rng(7);
int main(){
	ll checks=0;
	for(int t=0;t<1000000;t++){
		const int G=t%2?4:12;
		auto g=[&](){return Point((int)(rng()%G),(int)(rng()%G));};
		Point s=g(),e=g(),p=g();
		// brute: p is s+(e-s)*k/m for some integers, i.e. collinear and inside the box
		ll cr=(ll)((e.x-s.x)*(p.y-s.y)-(e.y-s.y)*(p.x-s.x));
		bool in=cr==0&&min(s.x,e.x)<=p.x&&p.x<=max(s.x,e.x)
			&&min(s.y,e.y)<=p.y&&p.y<=max(s.y,e.y);
		assert(onSegment(s,e,p)==in);
		checks++;
	}
	// floating point: points on the segment s+(e-s)*k
	for(int t=0;t<100000;t++){
		Point s(rng()%1000/7.0,rng()%1000/7.0),e(rng()%1000/7.0,rng()%1000/7.0);
		double k=rng()%1001/1000.0;
		Point p=s+(e-s)*k;
		assert(onSegment(s,e,p));
		Point q=s+(e-s)*(1.01+k);
		if(!(s==e))assert(!onSegment(s,e,q));
		checks+=2;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
