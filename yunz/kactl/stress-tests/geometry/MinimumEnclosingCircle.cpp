#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/MinimumEnclosingCircle.h"

int main(){
	srand(2);
	ll checks=0;
	for(int it=0;it<300000;it++){
		int N=rand()%20+1;
		vector<Point>ps;
		for(int i=0;i<N;i++)ps.emplace_back(rand()%21-10,rand()%21-10);
		pair<Point,double>pa=mec(ps);
		Point mid=pa.first;
		double rad=pa.second,maxDist=0;
		for(Point p:ps)maxDist=max(maxDist,(p-mid).len());
		assert(fabs(maxDist-rad)<1e-6);
		// moving the center a little in any direction does not help
		for(int it2=0;it2<50;it2++){
			Point q2=mid-Point(0,1e-6).rotate(it2);
			bool ok=false;
			for(Point p:ps)if((p-q2).len()>rad-1e-7)ok=true;
			assert(ok);
		}
		checks++;
	}
	// larger cases: n=1000 random real points
	mt19937 rng(11);
	for(int it=0;it<20;it++){
		vector<Point>ps;
		for(int i=0;i<1000;i++)ps.emplace_back(rng()%2001/100.0-10,rng()%2001/100.0-10);
		pair<Point,double>pa=mec(ps);
		double mx=0;
		for(Point p:ps)mx=max(mx,(p-pa.first).len());
		assert(fabs(mx-pa.second)<1e-6);
		for(int it2=0;it2<50;it2++){
			Point q2=pa.first-Point(0,1e-6).rotate(it2);
			bool ok=false;
			for(Point p:ps)if((p-q2).len()>pa.second-1e-7)ok=true;
			assert(ok);
		}
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
