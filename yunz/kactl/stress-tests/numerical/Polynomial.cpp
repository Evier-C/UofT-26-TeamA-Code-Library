#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/Polynomial.h"

mt19937 rng(1);
double rd(){return (int)(rng()%2001)/100.0-10;}
int main(){
	long long checks=0;
	{ // Usage 示例
		vector<double> a={2,-3,1};
		assert(fabs(peval(a,0.5)-0.75)<1e-12);
		pdivroot(a,1);
		assert(a.size()==2&&fabs(a[0]+2)<1e-12&&fabs(a[1]-1)<1e-12);
		pderiv(a);
		assert(a.size()==1&&fabs(a[0]-1)<1e-12);
		checks+=3;
	}
	for(int it=0;it<20000;it++){
		int n=rng()%8+1;
		vector<double> a(n);
		for(auto&v:a)v=rd();
		double x=rd()/5;
		double want=0;
		for(int i=0;i<n;i++)want+=a[i]*pow(x,i);
		assert(fabs(peval(a,x)-want)<1e-6*max(1.0,fabs(want)));
		// 求导
		vector<double> d=a;
		pderiv(d);
		assert((int)d.size()==n-1);
		for(int i=0;i+1<n;i++)assert(fabs(d[i]-(i+1)*a[i+1])<1e-9);
		// 除以 (x-r): 构造 a=(x-r)*q
		double r=rd();
		vector<double> p(n+1,0);
		for(int i=0;i<n;i++)p[i+1]+=a[i],p[i]-=r*a[i];
		pdivroot(p,r);
		assert((int)p.size()==n);
		for(int i=0;i<n;i++)
			assert(fabs(p[i]-a[i])<1e-6*max(1.0,fabs(a[i])));
		checks+=3;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
