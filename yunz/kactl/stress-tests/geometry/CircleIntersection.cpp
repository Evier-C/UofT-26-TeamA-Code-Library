#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/CircleIntersection.h"

int main(){
	srand(2);
	ll checks=0;
	for(int it=0;it<100000;it++){
		double rnd[4];
		for(int i=0;i<4;i++)rnd[i]=rand()%21-10;
		Point a(rnd[0],rnd[1]),b(rnd[2],rnd[3]);
		double ra=rand()%10,rb=rand()%10;
		if(a==b)continue;
		pair<Point,Point>out;
		bool ret=circleInter(a,b,ra,rb,out);
		if(ret){
			assert(fabs((out.first-a).len()-ra)<1e-9);
			assert(fabs((out.second-a).len()-ra)<1e-9);
			assert(fabs((out.first-b).len()-rb)<1e-9);
			assert(fabs((out.second-b).len()-rb)<1e-9);
		}
		// brute: hill-climb a common point
		auto func=[&](Point x){
			double d1=(x-a).len()-ra,d2=(x-b).len()-rb;
			return d1*d1+d2*d2;
		};
		Point start=(a+b)/2+(a-b).perp();
		double cv=func(start);Point cp=start;
		bool slow=false;
		for(double jmp=100;jmp>1e-20&&!slow;jmp/=2){
			int iters=0;
			for(int imp=1;imp--;){
				if(++iters==100){slow=true;break;}
				for(int dx=-1;dx<=1;dx++)for(int dy=-1;dy<=1;dy++){
					Point p(cp.x+dx*jmp,cp.y+dy*jmp);
					double v=func(p);
					if(v<cv)cv=v,cp=p,imp=1;
				}
			}
		}
		if(slow)continue; // hill-climbing is sometimes slow
		if(fabs((cp-a).len()-ra)<1e-9&&fabs((cp-b).len()-rb)<1e-9){
			assert(ret);
			assert((out.first-cp).len()<1e-6||(out.second-cp).len()<1e-6);
		}else assert(!ret);
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
