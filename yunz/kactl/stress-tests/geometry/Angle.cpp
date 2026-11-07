#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/Angle.h"

typedef long double ld;
const ld PI2=2*acosl(-1);
mt19937 rng(9);
// angle in [0, 2pi) plus t turns
ld key(Angle a){
	ld r=atan2l(a.y,a.x);
	if(r<0)r+=PI2;
	return r+a.t*PI2;
}
// exact brute comparison: same direction checked with integers
int cmpBrute(Angle a,Angle b){
	if(a.t!=b.t)return a.t<b.t?-1:1;
	ll cr=(ll)a.x*b.y-(ll)a.y*b.x,dt=(ll)a.x*b.x+(ll)a.y*b.y;
	if(cr==0&&dt>0)return 0;
	return key(a)<key(b)?-1:1;
}
Angle randAngle(int G,int maxT){
	int x,y;
	do{x=(int)(rng()%(2*G+1))-G;y=(int)(rng()%(2*G+1))-G;}while(!x&&!y);
	return Angle(x,y,(int)(rng()%(maxT+1)));
}
int main(){
	ll checks=0;
	for(int it=0;it<500000;it++){
		int G=it%2?3:1000;
		Angle a=randAngle(G,2),b=randAngle(G,2);
		int c=cmpBrute(a,b);
		assert((a<b)==(c<0));
		assert((b<a)==(c>0));
		assert(fabsl(key(a.t90())-key(a)-PI2/4)<1e-9);
		assert(fabsl(key(a.t180())-key(a)-PI2/2)<1e-9);
		assert(fabsl(key(a.t360())-key(a)-PI2)<1e-9);
		Angle d=angleDiff(a,b);
		assert(fabsl(key(d)-(key(b)-key(a)))<1e-9);
		// segmentAngles takes two points (t = 0)
		pair<Angle,Angle>s=segmentAngles(Angle(a.x,a.y),Angle(b.x,b.y));
		ld w=key(s.second)-key(s.first);
		assert(w>-1e-12&&w<=PI2/2+1e-9);
		checks+=7;
		// point + vector: result direction is within pi of a
		Angle v=randAngle(G,0);
		if((ll)(a.x+v.x)==0&&(ll)(a.y+v.y)==0)continue;
		Angle r=a+v;
		assert(r.x==a.x+v.x&&r.y==a.y+v.y);
		ld df=key(r)-key(a);
		assert(df>-PI2/2-1e-9&&df<PI2/2+1e-9);
		checks+=2;
	}
	// the sweep from the usage: count angles in [v[i], v[i]+pi)
	for(int it=0;it<3000;it++){
		int n=rng()%30+1,G=it%2?3:100;
		vector<Angle>v;
		for(int i=0;i<n;i++)v.push_back(randAngle(G,0));
		sort(v.begin(),v.end());
		for(int i=0;i+1<n;i++)assert(key(v[i])<=key(v[i+1])+1e-12);
		for(int i=0;i<n;i++)v.push_back(v[i].t360());
		for(int i=0,j=0;i<n;i++){
			while(v[j]<v[i].t180())j++;
			int cnt=0;
			for(int k=0;k<n;k++){
				ll cr=(ll)v[i].x*v[k].y-(ll)v[i].y*v[k].x;
				ll dt=(ll)v[i].x*v[k].x+(ll)v[i].y*v[k].y;
				// angle from v[i] to v[k] in (0, pi), or same direction
				// and not before i in sorted order
				if(cr>0||(cr==0&&dt>0&&k>=i))cnt++;
			}
			assert(j-i==cnt);
			checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
