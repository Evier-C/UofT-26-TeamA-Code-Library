#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/HullDiameter.h"

mt19937 rng(18);
int main(){
	ll checks=0;
	for(int it=0;it<1000000;it++){
		int N=it%100==0?rng()%300+1:rng()%10+1,G=it%2?11:2001;
		vector<Point>ps;
		for(int i=0;i<N;i++)ps.emplace_back((int)(rng()%G)-G/2,(int)(rng()%G)-G/2);
		T r1=0;
		for(int i=0;i<N;i++)for(int j=0;j<i;j++)r1=max(r1,len2(ps[i]-ps[j]));
		vector<Point>h=convexHull(ps);
		assert(hullDiameter(h)==r1);
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
