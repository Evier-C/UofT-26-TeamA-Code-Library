#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/PointInsideHull.h"
#include "../../content/geometry/InsidePolygon.h"

mt19937 rng(19);
// brute: 1 strictly inside, 2 on boundary, 0 outside
int brute(vector<Point>&h,Point p){
	int m=h.size();
	if(m==1)return h[0]==p?2:0;
	if(m==2)return onSegment(h[0],h[1],p)?2:0;
	bool bd=false;
	for(int i=0;i<m;i++){
		T c=cross(h[i],h[(i+1)%m],p);
		if(c<0)return 0;
		if(c==0)bd=true;
	}
	return bd?2:1;
}
int main(){
	ll checks=0;
	for(int it=0;it<200000;it++){
		int N=rng()%15+1,G=it%2?20:6;
		vector<Point>ps;
		for(int i=0;i<N;i++)ps.emplace_back((int)(rng()%G)-G/2,(int)(rng()%G)-G/2);
		vector<Point>h=convexHull(ps);
		for(int k=0;k<20;k++){
			Point p((int)(rng()%(G+2))-G/2-1,(int)(rng()%(G+2))-G/2-1);
			int b=brute(h,p);
			assert(inHull(h,p,true)==(b==1));
			assert(inHull(h,p,false)==(b>=1));
			if(h.size()>=3){
				assert(inPolygon(h,p,true)==inHull(h,p,true));
				assert(inPolygon(h,p,false)==inHull(h,p,false));
			}
			checks+=2;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
