#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/PolyInterpolate.h"

mt19937 rng(2);
int main(){
	long long checks=0;
	{
		vector<double> a=interpolate({0,1,2},{1,2,5});
		assert(a.size()==3);
		assert(fabs(a[0]-1)<1e-9&&fabs(a[1])<1e-9&&fabs(a[2]-1)<1e-9);
		checks++;
	}
	for(int it=0;it<20000;it++){
		int n=rng()%7+1;
		vector<double> c(n);
		for(auto&v:c)v=(int)(rng()%21)-10;
		// 互不相同的整数点
		set<int> used;
		vector<double> x,y;
		while((int)x.size()<n){
			int v=(int)(rng()%21)-10;
			if(used.count(v))continue;
			used.insert(v);
			double s=0;
			for(int i=n-1;i>=0;i--)s=s*v+c[i];
			x.push_back(v);y.push_back(s);
		}
		vector<double> a=interpolate(x,y);
		assert((int)a.size()==n);
		for(int i=0;i<n;i++)assert(fabs(a[i]-c[i])<1e-5);
		checks++;
	}
	// 切比雪夫点, 较大 n
	for(int n:{10,15,20}){
		vector<double> x(n),y(n);
		for(int k=0;k<n;k++){
			x[k]=cos(k*acos(-1.0)/(n-1));
			y[k]=exp(x[k]);
		}
		vector<double> a=interpolate(x,y);
		for(double t=-1;t<=1;t+=0.01){
			double s=0;
			for(int i=n-1;i>=0;i--)s=s*t+a[i];
			assert(fabs(s-exp(t))<1e-6);
			checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
