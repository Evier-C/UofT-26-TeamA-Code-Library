#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/PolygonArea.h"
#include "../../content/geometry/InsidePolygon.h"

int main(){
	ll checks=0;
	mt19937 rng(13);
	// brute: trapezoid formula, sum of (x[i+1]-x[i])*(y[i]+y[i+1])
	for(int it=0;it<300000;it++){
		int n=rng()%10+1,G=it%2?5:1000;
		vector<Point>v;
		for(int i=0;i<n;i++)v.push_back(Point((int)(rng()%(2*G+1))-G,(int)(rng()%(2*G+1))-G));
		ll want=0;
		for(int i=0;i<n;i++){
			Point a=v[i],b=v[(i+1)%n];
			want-=(ll)(b.x-a.x)*(ll)(a.y+b.y);
		}
		assert(polygonArea2(v)==want);
		reverse(v.begin(),v.end());
		assert(polygonArea2(v)==-want);
		checks+=2;
	}
	// Monte Carlo on a triangle
	srand(0);
	vector<Point>ps={Point(0,0),Point(6,4),Point(0,9)};
	int count=0;
	for(int it=0;it<100000;it++){
		double x=rand()/(RAND_MAX+1.0)*10,y=rand()/(RAND_MAX+1.0)*10;
		if(inPolygon(ps,Point(x,y),true))count++;
	}
	double approxArea=(double)count/100000*100;
	assert(fabs(polygonArea2(ps)/2.0-approxArea)<1);
	assert(polygonArea2(ps)==54);
	cout<<"Tests passed! ("<<checks+2<<" checks)"<<endl;
}
