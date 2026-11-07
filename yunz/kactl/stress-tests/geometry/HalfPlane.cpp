#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/HalfPlane.h"
#include "../../content/geometry/PolygonCut.h"
#include "../../content/geometry/PolygonArea.h"

mt19937 rng(16);
// brute: start from the bounding box and cut by every line
vector<Point>brute(vector<Line>&L,double B){
	vector<Point>p={Point(-B,-B),Point(B,-B),Point(B,B),Point(-B,B)};
	for(Line l:L)p=polygonCut(p,l.e,l.s); // keep the left side of s->e
	return p;
}
int main(){
	ll checks=0,empty=0,nonempty=0;
	for(int it=0;it<300000;it++){
		int n=rng()%8+1,G=it%3==0?3:(it%3==1?10:1000);
		double B=G+5;
		vector<Line>L;
		for(int i=0;i<n;i++){
			Point s((int)(rng()%(2*G+1))-G,(int)(rng()%(2*G+1))-G);
			Point e((int)(rng()%(2*G+1))-G,(int)(rng()%(2*G+1))-G);
			if(s==e){i--;continue;}
			L.push_back({s,e});
		}
		vector<Point>want=brute(L,B);
		// add the box (counter-clockwise) to make it bounded
		L.push_back({Point(-B,-B),Point(B,-B)});
		L.push_back({Point(B,-B),Point(B,B)});
		L.push_back({Point(B,B),Point(-B,B)});
		L.push_back({Point(-B,B),Point(-B,-B)});
		shuffle(L.begin(),L.end(),rng);
		vector<Point>got=halfPlane(L);
		double wa=fabs(polygonArea2(want))/2,ga=polygonArea2(got)/2;
		assert(ga>-1e-9); // counter-clockwise
		assert(fabs(wa-ga)<1e-6*max(1.0,wa));
		if(got.empty())assert(wa<1e-6),empty++;
		else{
			nonempty++;
			// every vertex is inside every half-plane
			for(Point v:got)for(Line l:L)
				assert(l.s.cross(l.e,v)/(l.e-l.s).len()>-1e-6*B);
			// convex
			int m=got.size();
			for(int i=0;i<m;i++)
				assert(got[i].cross(got[(i+1)%m],got[(i+2)%m])>-1e-6*B*B);
		}
		checks++;
	}
	assert(empty>1000&&nonempty>1000);
	// usage example: a unit square
	vector<Line>L={{Point(0,0),Point(1,0)},{Point(1,0),Point(1,1)},
		{Point(1,1),Point(0,1)},{Point(0,1),Point(0,0)},{Point(5,5),Point(4,6)}};
	vector<Point>poly=halfPlane(L);
	assert(poly.size()==4&&fabs(polygonArea2(poly)-2)<1e-9);
	cout<<"Tests passed! ("<<checks+1<<" checks)"<<endl;
}
