#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/lineDistance.h"

typedef long double ld;
mt19937 rng(2);
double rr(double lo,double hi){return uniform_real_distribution<double>(lo,hi)(rng);}

int main(){
	ll checks=0;
	for(int it=0;it<500000;it++){
		Point a,b,p;
		if(it%2){
			a=Point(rng()%21-10.0,rng()%21-10.0);b=Point(rng()%21-10.0,rng()%21-10.0);
			p=Point(rng()%21-10.0,rng()%21-10.0);
		}else{
			a=Point(rr(-100,100),rr(-100,100));b=Point(rr(-100,100),rr(-100,100));
			p=Point(rr(-100,100),rr(-100,100));
		}
		if(a==b)continue;
		double d=lineDist(a,b,p);
		// brute: foot of perpendicular
		ld dx=b.x-a.x,dy=b.y-a.y,t=((p.x-a.x)*dx+(p.y-a.y)*dy)/(dx*dx+dy*dy);
		ld fx=a.x+t*dx,fy=a.y+t*dy,dist=hypotl(p.x-fx,p.y-fy);
		assert(fabsl(fabs(d)-dist)<1e-7);
		ld cr=dx*(p.y-a.y)-dy*(p.x-a.x);
		if(fabsl(cr)>1e-6)assert((d>0)==(cr>0));
		checks+=2;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
