#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/ConvexHull.h"

// old KACTL hull on indices (reference)
pair<vector<int>,vector<int>>ulHull(vector<Point>&S){
	vector<int>Q(S.size()),U,L;
	iota(Q.begin(),Q.end(),0);
	sort(Q.begin(),Q.end(),[&S](int a,int b){
		return make_pair(S[a].x,S[a].y)<make_pair(S[b].x,S[b].y);});
	for(int it:Q){
		while(U.size()>1&&cross(S[U[U.size()-2]],S[it],S[U.back()])<=0)U.pop_back();
		U.push_back(it);
		while(L.size()>1&&cross(S[L[L.size()-2]],S[it],S[L.back()])>=0)L.pop_back();
		L.push_back(it);
	}
	return {U,L};
}
vector<int>oldHull(vector<Point>&S){
	auto [u,l]=ulHull(S);
	if(S.size()<=1)return u;
	if(S[u[0]]==S[u[1]])return {0};
	l.insert(l.end(),u.rbegin()+1,u.rend()-1);
	return l;
}
mt19937 rng(17);
int main(){
	ll checks=0;
	for(int t=0;t<100000;t++){
		int SZ=t%2?100:rng()%12+1,G=t%4<2?1000:(t%4==2?3:6);
		vector<Point>pts(SZ);
		for(int i=0;i<SZ;i++)pts[i]=Point((int)(rng()%G),(int)(rng()%G));
		if(t%8==7)for(int i=0;i<SZ;i++)pts[i]=Point(pts[0].x+i%3,pts[0].y+2*(i%3)); // collinear
		vector<Point>res=convexHull(pts);
		vector<int>res2=oldHull(pts);
		assert(res.size()==res2.size());
		for(int i=0;i<(int)res2.size();i++)assert(pts[res2[i]]==res[i]);
		// properties: strictly convex, counter-clockwise, contains all points
		int m=res.size();
		assert(res[0]==*min_element(pts.begin(),pts.end()));
		if(m>=3){
			for(int i=0;i<m;i++){
				assert(cross(res[i],res[(i+1)%m],res[(i+2)%m])>0);
				for(Point p:pts)assert(cross(res[i],res[(i+1)%m],p)>=0);
			}
		}
		checks+=2;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
