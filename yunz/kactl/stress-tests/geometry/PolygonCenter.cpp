#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/PolygonCenter.h"
#include "../../content/geometry/InsidePolygon.h"

mt19937 rng(14);
int main(){
	ll checks=0;
	// star-shaped polygons around c: centroid as a weighted sum of triangles (c, v[i], v[i+1])
	for(int it=0;it<200000;it++){
		int n=rng()%10+3,G=it%2?6:1000;
		vector<Point>v;
		for(int i=0;i<n;i++)v.push_back(Point((int)(rng()%G),(int)(rng()%G)));
		Point c(0,0);
		for(Point q:v)c=c+q;
		c=c/(T)n+Point(0.0123,0.0456);
		sort(v.begin(),v.end(),[&](Point a,Point b){return (a-c).angle()<(b-c).angle();});
		if(it%3==0)reverse(v.begin(),v.end());
		long double A=0,sx=0,sy=0;
		for(int i=0;i<n;i++){
			Point a=v[i],b=v[(i+1)%n];
			long double w=(a-c).cross(b-c);
			A+=w;sx+=w*(c.x+a.x+b.x)/3;sy+=w*(c.y+a.y+b.y)/3;
		}
		if(fabsl(A)<1e-3*G)continue;
		Point p=polygonCenter(v);
		assert(fabsl(p.x-sx/A)<1e-6*G&&fabsl(p.y-sy/A)<1e-6*G);
		checks++;
	}
	// Monte Carlo on a triangle and a concave polygon
	srand(0);
	vector<vector<Point>>polys={{Point(0,0),Point(6,4),Point(0,9)},
		{Point(0,0),Point(10,0),Point(10,10),Point(5,2),Point(0,10)}};
	for(vector<Point>ps:polys){
		int count=0;Point su(0,0);
		for(int it=0;it<200000;it++){
			Point q(rand()/(RAND_MAX+1.0)*10,rand()/(RAND_MAX+1.0)*10);
			if(!inPolygon(ps,q,true))continue;
			count++;su=su+q;
		}
		su=su/count;
		Point p=polygonCenter(ps);
		assert(fabs(p.x-su.x)<1e-1&&fabs(p.y-su.y)<1e-1);
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
