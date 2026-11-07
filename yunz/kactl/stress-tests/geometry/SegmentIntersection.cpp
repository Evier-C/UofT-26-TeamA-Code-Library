#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/SegmentIntersection.h"

// old KACTL implementation (exact on integer coordinates)
int oldInter(Point s1,Point e1,Point s2,Point e2,Point&r1,Point&r2){
	if(e1.x==s1.x&&e1.y==s1.y){
		if(e2.x==s2.x&&e2.y==s2.y){
			if(e1.x==e2.x&&e1.y==e2.y){r1=e1;return 1;}
			return 0;
		}
		return oldInter(s2,e2,s1,e1,r1,r2);
	}
	Point v1=e1-s1,v2=e2-s2,d=s2-s1;
	T a=v1.cross(v2),a1=v1.cross(d),a2=v2.cross(d);
	if(a==0){
		T b1=s1.dot(v1),c1=e1.dot(v1),b2=s2.dot(v1),c2=e2.dot(v1);
		if(a1||a2||max(b1,min(b2,c2))>min(c1,max(b2,c2)))return 0;
		r1=min(b2,c2)<b1?s1:(b2<c2?s2:e2);
		r2=max(b2,c2)>c1?e1:(b2>c2?s2:e2);
		return 2-(r1.x==r2.x&&r1.y==r2.y);
	}
	if(a<0){a=-a;a1=-a1;a2=-a2;}
	if(0<a1||a<-a1||0<a2||a<-a2)return 0;
	r1=s1-v1*a2/a;
	return 1;
}
bool eq(Point a,Point b){return (a-b).len()<1e-8;}
mt19937 rng(4);
int main(){
	ll checks=0;
	for(int t=0;t<1000000;t++){
		int G=t%3==0?3:(t%3==1?6:30);
		auto g=[&](){return Point((int)(rng()%G),(int)(rng()%G));};
		Point a=g(),b=g(),c=g(),d=g(),r1,r2;
		int res=oldInter(a,b,c,d,r1,r2);
		vector<Point>v=segInter(a,b,c,d);
		assert(res==(int)v.size());
		if(res==1)assert(eq(v[0],r1));
		else if(res==2){
			vector<Point>w={r1,r2};
			sort(w.begin(),w.end());
			assert(eq(v[0],w[0])&&eq(v[1],w[1]));
		}
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
