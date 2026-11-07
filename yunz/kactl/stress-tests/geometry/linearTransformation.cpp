#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/linearTransformation.h"

typedef complex<long double> C;
mt19937 rng(8);
double rr(double lo,double hi){return uniform_real_distribution<double>(lo,hi)(rng);}
int main(){
	ll checks=0;
	for(int t=0;t<500000;t++){
		auto g=[&](){return Point(rr(-10,10),rr(-10,10));};
		Point p0=g(),p1=g(),q0=g(),q1=g(),r=g();
		if((p1-p0).len()<1e-3)continue;
		Point r2=linearTransformation(p0,p1,q0,q1,r);
		// brute: z -> q0+(z-p0)*(q1-q0)/(p1-p0) in complex numbers
		C P0(p0.x,p0.y),P1(p1.x,p1.y),Q0(q0.x,q0.y),Q1(q1.x,q1.y),R(r.x,r.y);
		C W=Q0+(R-P0)*(Q1-Q0)/(P1-P0);
		assert(abs(W-C(r2.x,r2.y))<1e-6);
		Point a=linearTransformation(p0,p1,q0,q1,p0),b=linearTransformation(p0,p1,q0,q1,p1);
		assert((a-q0).len()<1e-6&&(b-q1).len()<1e-6);
		checks+=2;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
