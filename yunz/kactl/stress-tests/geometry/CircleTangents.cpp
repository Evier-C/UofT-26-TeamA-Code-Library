#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/CircleTangents.h"
#include "../../content/geometry/lineDistance.h"

Point randIntPt(int lim){return Point(rand()%(lim*2)-lim,rand()%(lim*2)-lim);}
int main(){
	ll checks=0;
	int cnt[3]={0,0,0};
	for(int i=0;i<1000000;i++){
		Point c1=randIntPt(5),c2=randIntPt(5);
		double r1=sqrt(rand()%20),r2=sqrt(rand()%20);
		for(int s=-1;s<=1;s+=2){
			vector<pair<Point,Point>>tans=tangents(c1,r1,c2,s*r2);
			// brute count: external tangents exist iff d >= |r1-r2|,
			// internal ones iff d >= r1+r2 (one tangent when equal)
			double d=(c2-c1).len(),need=fabs(r1-s*r2);
			int want;
			if(d<1e-12)want=0;
			else if(fabs(d-need)<1e-9)want=1;
			else want=d>need?2:0;
			assert((int)tans.size()==want);
			cnt[want]++;
			if(tans.size()==1){
				assert((tans[0].first-tans[0].second).len()<1e-8);
				assert(fabs((tans[0].first-c1).len()-r1)<1e-8);
				assert(fabs((tans[0].first-c2).len()-r2)<1e-8);
			}else if(tans.size()==2){
				for(auto l:tans){
					assert(fabs((l.first-c1).len()-r1)<1e-8);
					assert(fabs((l.second-c2).len()-r2)<1e-8);
					if((l.first-l.second).len()>1e-6){
						assert(fabs(fabs(lineDist(l.first,l.second,c1))-r1)<1e-8);
						assert(fabs(fabs(lineDist(l.first,l.second,c2))-r2)<1e-8);
					}
				}
			}
			checks++;
		}
	}
	assert(cnt[0]&&cnt[1]&&cnt[2]);
	// tangents from a point to a circle (r2 = 0)
	vector<pair<Point,Point>>v=tangents(Point(0,0),1,Point(2,0),0);
	assert(v.size()==2);
	for(auto l:v)assert(fabs(l.first.dot(l.first-Point(2,0)))<1e-9&&(l.second-Point(2,0)).len()<1e-9);
	cout<<"Tests passed! ("<<checks+1<<" checks)"<<endl;
}
