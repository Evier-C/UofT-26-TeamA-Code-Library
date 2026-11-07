#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/LineHullIntersection.h"

// old KACTL segment intersection (exact on integer input)
int segmentIntersection(Point s1,Point e1,Point s2,Point e2,Point&r1,Point&r2){
	if(e1==s1){
		if(e2==s2){
			if(e1==e2){r1=e1;return 1;}
			return 0;
		}
		return segmentIntersection(s2,e2,s1,e1,r1,r2);
	}
	Point v1=e1-s1,v2=e2-s2,d=s2-s1;
	T a=v1.cross(v2),a1=v1.cross(d),a2=v2.cross(d);
	if(a==0){
		T b1=s1.dot(v1),c1=e1.dot(v1),b2=s2.dot(v1),c2=e2.dot(v1);
		if(a1||a2||max(b1,min(b2,c2))>min(c1,max(b2,c2)))return 0;
		r1=min(b2,c2)<b1?s1:(b2<c2?s2:e2);
		r2=max(b2,c2)>c1?e1:(b2>c2?s2:e2);
		return 2-(r1==r2);
	}
	if(a<0){a=-a;a1=-a1;a2=-a2;}
	if(0<a1||a<-a1||0<a2||a<-a2)return 0;
	r1=s1-v1*a2/a;
	return 1;
}
mt19937 rng(20);
int R(){return (int)(rng()%20)-10;}
int main(){
	ll checks=0;
	for(int it=0;it<1000000;it++){
		int N=rng()%15;
		vector<Point>ps2;
		for(int i=0;i<N;i++)ps2.emplace_back(R(),R());
		vector<Point>ps=convexHull(ps2);
		if(ps.empty())continue;
		Point p(R(),R()),q(R(),R());
		N=ps.size();
		Point delta=q-p,farp=p-delta*50,farq=p+delta*50;
		array<int,2>res=lineHull(p,q,ps);
		pair<int,int>r={res[0],res[1]};
		if(p==q)continue;
		int any=0,gen=0,corner=-1,waspar=0;
		vector<pair<Point,int>>hits;
		for(int iter=0;iter<2;iter++)for(int i=0;i<N;i++){
			Point r1,r2;
			int j=(i+1)%N;
			int qu=segmentIntersection(farp,farq,ps[i],ps[j],r1,r2);
			if(qu&&(q-p).cross(ps[j]-ps[i])==0){ // parallel
				if(N!=2)assert(r.first==i||r.second==i);
				any=1;
				if(iter==0)gen=10;
				waspar=1;
			}else if(qu){
				assert(qu!=2);
				if(r1==ps[i]){
					int k=(i-1+N)%N;
					assert(r.first==i||r.second==i||r.first==k||r.second==k);
					if(iter==1&&!waspar)assert(r.first==i||r.second==i);
					if(iter==0)corner=i,gen++,hits.emplace_back(r1,i);
				}else if(r1==ps[j]){
					assert(r.first==i||r.second==i||r.first==j||r.second==j);
					if(iter==1&&!waspar)assert(r.first==j||r.second==j);
					if(iter==0)corner=j,gen++;
				}else{
					assert(r.first==i||r.second==i);
					if(iter==0)gen=10,hits.emplace_back(r1,i);
				}
				any=1;
			}
		}
		checks++;
		if(!any){
			assert(r.first==-1&&r.second==-1);
			continue;
		}
		if(!waspar)assert(r.first!=r.second);
		if(gen==2){
			assert(r.first==corner);
			assert(r.second==-1);
		}
		if(N>2)assert(((int)hits.size()==1)==(r.second==-1||r.first==r.second));
		assert(hits.size()<=2);
		if(r.first!=r.second&&hits.size()==2){
			assert(r.second!=-1);
			assert(hits[0].second!=hits[1].second);
			assert(hits[0].second==r.first||hits[0].second==r.second);
			assert(hits[1].second==r.first||hits[1].second==r.second);
			double dist0=(hits[0].first-p).dot(delta),dist1=(hits[1].first-p).dot(delta);
			if(hits[0].second==r.first)assert(dist0<=dist1);
			else assert(dist0>=dist1);
		}
		res=lineHull(q,p,ps);
		pair<int,int>Rr={res[0],res[1]};
		if(r.second==-1)assert(Rr==r);
		else if(N==2&&r.first==r.second)assert(Rr.first==Rr.second);
		else assert(Rr.first==r.second&&Rr.second==r.first);
	}
	// extrVertex against brute force
	for(int it=0;it<200000;it++){
		int N=rng()%15+1;
		vector<Point>ps2;
		for(int i=0;i<N;i++)ps2.emplace_back(R(),R());
		vector<Point>ps=convexHull(ps2);
		Point dir(R(),R());
		if(dir==Point(0,0))continue;
		int i=extrVertex(ps,dir);
		T best=-1e18;
		for(Point v:ps)best=max(best,v.dot(dir));
		assert(ps[i].dot(dir)==best);
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
