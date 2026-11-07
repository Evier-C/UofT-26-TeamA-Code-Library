#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/lineIntersection.h"

mt19937 rng(5);
double rr(double lo,double hi){return uniform_real_distribution<double>(lo,hi)(rng);}
// distance from p to line ab (brute)
double dist(Point a,Point b,Point p){
	long double dx=b.x-a.x,dy=b.y-a.y;
	return fabsl(dx*(p.y-a.y)-dy*(p.x-a.x))/hypotl(dx,dy);
}
int main(){
	ll checks=0;
	for(int t=0;t<1000000;t++){
		Point a,b,c,d;
		if(t%4){
			const int G=t%4==1?4:10;
			auto g=[&](){return Point((int)(rng()%G),(int)(rng()%G));};
			a=g(),b=g(),c=g(),d=g();
		}else{
			a=Point(rr(-50,50),rr(-50,50)),b=Point(rr(-50,50),rr(-50,50));
			c=Point(rr(-50,50),rr(-50,50)),d=Point(rr(-50,50),rr(-50,50));
		}
		if(a==b||c==d)continue;
		pair<int,Point>r=lineInter(a,b,c,d);
		// exact classification for integer points
		if(t%4){
			T cr=cross(b-a,d-c);
			if(cr!=0)assert(r.first==1);
			else if(cross(b-a,c-a)==0)assert(r.first==-1);
			else assert(r.first==0);
		}
		if(r.first==1){
			assert(dist(a,b,r.second)<1e-7);
			assert(dist(c,d,r.second)<1e-7);
		}
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
