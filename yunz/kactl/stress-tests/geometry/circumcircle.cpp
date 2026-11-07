#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/circumcircle.h"

mt19937 rng(10);
double rr(double lo,double hi){return uniform_real_distribution<double>(lo,hi)(rng);}
int main(){
	ll checks=0;
	for(int it=0;it<500000;it++){
		Point A,B,C;
		if(it%2){
			auto g=[&](){return Point((int)(rng()%21)-10,(int)(rng()%21)-10);};
			A=g(),B=g(),C=g();
		}else A=Point(rr(-10,10),rr(-10,10)),B=Point(rr(-10,10),rr(-10,10)),C=Point(rr(-10,10),rr(-10,10));
		if(fabs(cross(A,B,C))<1e-2)continue;
		double r=ccRadius(A,B,C);Point o=ccCenter(A,B,C);
		// brute: center is equidistant from the three points
		assert(fabs(len(o-A)-r)<1e-6*max(1.0,r));
		assert(fabs(len(o-B)-r)<1e-6*max(1.0,r));
		assert(fabs(len(o-C)-r)<1e-6*max(1.0,r));
		checks+=3;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
