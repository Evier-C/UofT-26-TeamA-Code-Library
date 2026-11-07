#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/PolygonArea.h"
#include "../../content/geometry/PolygonCut.h"
#include "../../content/geometry/sideOf.h"
#include "../../content/geometry/InsidePolygon.h"
#include "../../content/geometry/SegmentIntersection.h"

// polygon is simple: only adjacent edges meet, at one point
bool simple(vector<Point>&ps){
	int N=ps.size();
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++){
		vector<Point>r=segInter(ps[i],ps[(i+1)%N],ps[j],ps[(j+1)%N]);
		if(r.size()==2)return false;
		if(r.size()==1&&!(i+1==j||(j+1)%N==i))return false;
	}
	return true;
}
int main(){
	ll checks=0;
	// Monte Carlo area (ported from KACTL)
	srand(1);
	for(int it=0;it<500;it++){
		int N=rand()%10+3;
		vector<Point>ps;
		for(int i=0;i<N;i++)ps.emplace_back(rand()%10-5,rand()%10-5);
		Point p(rand()%10-5,rand()%10-5),q(rand()%10-5,rand()%10-5);
		if(!simple(ps)||p==q)continue;
		int count=0;
		const int ITS=200000;
		for(int k=0;k<ITS;k++){
			Point r(rand()/(RAND_MAX+1.0)*10-5,rand()/(RAND_MAX+1.0)*10-5);
			if(!inPolygon(ps,r,true))continue;
			if(sideOf(p,q,r)>0)continue;
			count++;
		}
		double approxArea=(double)count/ITS*100;
		vector<Point>res=polygonCut(ps,p,q);
		double realArea=res.empty()?0.0:fabs(polygonArea2(res)/2.0);
		assert(fabs(realArea-approxArea)<3e-1);
		checks++;
	}
	// exact: cutting by s->e and by e->s splits the signed area,
	// and no remaining vertex is to the left of s->e
	mt19937 rng(15);
	for(int it=0;it<300000;it++){
		int N=rng()%12+3,G=it%2?6:100;
		vector<Point>ps;
		for(int i=0;i<N;i++)ps.emplace_back((int)(rng()%G),(int)(rng()%G));
		Point s((int)(rng()%G),(int)(rng()%G)),e((int)(rng()%G),(int)(rng()%G));
		if(s==e)continue;
		vector<Point>a=polygonCut(ps,s,e),b=polygonCut(ps,e,s);
		assert(fabs(polygonArea2(a)+polygonArea2(b)-polygonArea2(ps))<1e-6*G*G);
		for(Point v:a)assert(sideOf(s,e,v,1e-7)<=0);
		for(Point v:b)assert(sideOf(s,e,v,1e-7)>=0);
		checks+=3;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
