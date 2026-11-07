#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/IntegrateAdaptive.h"

int type;
double P;
double f(double x){
	if(type==0)return sin(x);
	if(type==1)return x*x*x-P*x+1;
	if(type==2)return exp(P*x);
	if(type==3)return 1/(1+x*x);
	if(type==4)return sqrt(max(0.0,1-x*x)); // 半圆
	return fabs(x-P);
}
int main(){
	long long checks=0;
	const double pi=acos(-1.0);
	type=0;
	assert(fabs(integrate(0,pi)-2)<1e-7);
	assert(fabs(integrate(0,1,1e-10)-(1-cos(1.0)))<1e-9);
	checks+=2;
	mt19937 rng(6);
	for(int it=0;it<3000;it++){
		double l=(int)(rng()%2001)/100.0-10,r=l+(rng()%1000+1)/100.0;
		P=(int)(rng()%201)/100.0-1;
		type=1;
		auto F1=[&](double x){return x*x*x*x/4-P*x*x/2+x;};
		assert(fabs(integrate(l,r)-(F1(r)-F1(l)))<1e-6);
		type=2;
		double want=fabs(P)<1e-12?r-l:(exp(P*r)-exp(P*l))/P;
		assert(fabs(integrate(l,r)-want)<1e-6*max(1.0,fabs(want)));
		type=3;
		assert(fabs(integrate(l,r)-(atan(r)-atan(l)))<1e-6);
		type=5;
		auto F5=[&](double x){return x<P?-(P-x)*(P-x)/2:(x-P)*(x-P)/2;};
		assert(fabs(integrate(l,r)-(F5(r)-F5(l)))<1e-6);
		checks+=4;
	}
	type=4;
	assert(fabs(integrate(-1,1)-pi/2)<1e-6);
	checks++;
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
