#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/HullDiameter.h"

mt19937 rng(18);
ll checks=0;
// brute force over distinct input points
void check(vector<Point>ps){
	vector<Point>d=ps;
	sort(d.begin(),d.end());
	d.erase(unique(d.begin(),d.end()),d.end());
	int m=d.size();
	T r1=0;
	for(int i=0;i<m;i++)for(int j=0;j<i;j++)r1=max(r1,(d[i]-d[j]).len2());
	int cnt=0;
	for(int i=0;i<m;i++)for(int j=0;j<i;j++)if((d[i]-d[j]).len2()==r1)cnt++;
	vector<Point>h=convexHull(ps);
	assert(hullDiameter(h)==r1);
	assert(countDiameter(h)==cnt);
	// calling again on the same hull gives the same answers
	assert(hullDiameter(h)==r1&&countDiameter(h)==cnt);
	checks+=2;
}
int main(){
	for(int it=0;it<1000000;it++){
		int N=it%100==0?rng()%300+1:rng()%10+1,G=it%2?11:2001;
		if(it%4==3)G=3; // small grid: many ties
		vector<Point>ps;
		for(int i=0;i<N;i++)ps.emplace_back((int)(rng()%G)-G/2,(int)(rng()%G)-G/2);
		check(ps);
	}
	// lattice points on circles x^2+y^2=r2 (many diameters), with extra inner points
	vector<int>R2={1,2,5,25,50,65,325,1105,5525,27625};
	for(int r2:R2){
		vector<Point>circ;
		int r=sqrt(r2)+1;
		for(int x=-r;x<=r;x++)for(int y=-r;y<=r;y++)if(x*x+y*y==r2)circ.emplace_back(x,y);
		for(int it=0;it<300;it++){
			vector<Point>ps;
			for(Point p:circ)if(it==0||rng()%3)ps.push_back(p);
			int extra=rng()%5;
			for(int i=0;i<extra;i++)ps.emplace_back((int)(rng()%r)-r/2,(int)(rng()%r)-r/2);
			if(rng()%2)ps.push_back(ps.empty()?Point(0,0):ps[0]); // duplicate point
			if(ps.empty())continue;
			shuffle(ps.begin(),ps.end(),rng);
			check(ps);
		}
	}
	// regular polygons rounded to integers, and squares
	for(int n=1;n<=60;n++){
		vector<Point>ps;
		for(int i=0;i<n;i++)ps.emplace_back(round(1000*cos(2*M_PI*i/n)),round(1000*sin(2*M_PI*i/n)));
		check(ps);
	}
	check({Point(0,0),Point(1,0),Point(1,1),Point(0,1)});
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
