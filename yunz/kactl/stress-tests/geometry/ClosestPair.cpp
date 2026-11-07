#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/ClosestPair.h"

mt19937 rng(21);
T brute(vector<Point>&ps){
	T best=LLONG_MAX;int n=ps.size();
	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)best=min(best,len2(ps[i]-ps[j]));
	return best;
}
int main(){
	ll checks=0;
	// small cases against brute force
	for(int it=0;it<1000000;it++){
		int n=rng()%15+2,maxx=rng()%20+1,maxy=rng()%20+1;
		int bx=(int)(rng()%20)-10,by=(int)(rng()%20)-10;
		vector<Point>ps;
		for(int i=0;i<n;i++)ps.emplace_back((int)(rng()%maxx)+bx,(int)(rng()%maxy)+by);
		pair<Point,Point>pa=closest(ps);
		assert(len2(pa.first-pa.second)==brute(ps));
		// the two points are input points
		assert(count(ps.begin(),ps.end(),pa.first)&&count(ps.begin(),ps.end(),pa.second));
		checks++;
	}
	// larger cases (also real coordinates)
	for(int it=0;it<40;it++){
		int n=3000;
		vector<Point>ps;
		int mx=rng()%1000000+1,my=rng()%1000000+1;
		for(int i=0;i<n;i++){
			if(it%2)ps.emplace_back((int)(rng()%mx)-100,(int)(rng()%my)-100);
			else ps.emplace_back(rng()%mx/7.0,rng()%my/3.0);
		}
		pair<Point,Point>pa=closest(ps);
		T b=brute(ps);
		assert(fabs(len2(pa.first-pa.second)-b)<=1e-9*max((T)1,b));
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
