#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/InsidePolygon.h"

mt19937 rng(12);
// exact segment-touch test on integer points
ll cr(Point a,Point b,Point c){return (ll)((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x));}
bool onSeg(Point s,Point e,Point p){
	return cr(s,e,p)==0&&min(s.x,e.x)<=p.x&&p.x<=max(s.x,e.x)
		&&min(s.y,e.y)<=p.y&&p.y<=max(s.y,e.y);
}
bool segTouch(Point a,Point b,Point c,Point d){
	ll d1=cr(a,b,c),d2=cr(a,b,d),d3=cr(c,d,a),d4=cr(c,d,b);
	if(((d1>0&&d2<0)||(d1<0&&d2>0))&&((d3>0&&d4<0)||(d3<0&&d4>0)))return true;
	return onSeg(a,b,c)||onSeg(a,b,d)||onSeg(c,d,a)||onSeg(c,d,b);
}
bool simple(vector<Point>&p){
	int n=p.size();
	if(n<3)return false;
	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
		int i2=(i+1)%n,j2=(j+1)%n;
		if(j==i2||i==j2){ // adjacent edges may only share the vertex
			Point sh=j==i2?p[j]:p[i];
			Point o1=j==i2?p[i]:p[i2],o2=j==i2?p[j2]:p[j];
			if(cr(sh,o1,o2)==0&&(o1-sh).dot(o2-sh)>0)return false;
			continue;
		}
		if(segTouch(p[i],p[i2],p[j],p[j2]))return false;
	}
	return true;
}
// random simple polygon: points sorted by angle around an inner point
vector<Point>genPoly(int n,int G){
	while(true){
		vector<Point>p;
		for(int i=0;i<n;i++)p.push_back(Point((int)(rng()%G),(int)(rng()%G)));
		sort(p.begin(),p.end());
		p.erase(unique(p.begin(),p.end()),p.end());
		Point c(0,0);
		for(Point q:p)c=c+q;
		c=c/(T)p.size()+Point(0.0123,0.0456);
		sort(p.begin(),p.end(),[&](Point a,Point b){return (a-c).angle()<(b-c).angle();});
		if(rng()%2)reverse(p.begin(),p.end());
		if(simple(p))return p;
	}
}
// brute: on boundary exactly, otherwise winding number by angles
int brute(vector<Point>&p,Point a){
	int n=p.size();
	for(int i=0;i<n;i++)if(onSeg(p[i],p[(i+1)%n],a))return 2;
	long double s=0;
	for(int i=0;i<n;i++)s+=atan2l((p[i]-a).cross(p[(i+1)%n]-a),(p[i]-a).dot(p[(i+1)%n]-a));
	return fabsl(s)>3;
}
int main(){
	ll checks=0;
	int cnt[3]={0,0,0};
	auto test=[&](int numPolys,int n,int G){
		for(int it=0;it<numPolys;it++){
			vector<Point>poly=genPoly(n,G);
			for(int k=0;k<100;k++){
				Point p((int)(rng()%(G+2))-1,(int)(rng()%(G+2))-1);
				int b=brute(poly,p);
				cnt[b]++;
				assert(inPolygon(poly,p,true)==(b==1));
				assert(inPolygon(poly,p,false)==(b>=1));
				checks+=2;
			}
		}
	};
	test(3000,4,4);
	test(3000,8,6);
	test(1000,20,10);
	test(50,300,100);
	assert(cnt[0]&&cnt[1]&&cnt[2]);
	// usage example
	vector<Point>v={Point(4,4),Point(1,2),Point(2,1)};
	assert(inPolygon(v,Point(3,3),false)&&inPolygon(v,Point(3,3),true));
	assert(inPolygon(v,Point(1,2),false)&&!inPolygon(v,Point(1,2),true));
	cout<<"Tests passed! ("<<checks+1<<" checks)"<<endl;
}
