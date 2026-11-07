#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/GoldenSectionSearch.h"

int type;
double P,Q,R;
double f(double x){
	if(type==0)return 4+x+.3*x*x; // Usage 示例
	if(type==1)return P*(x-Q)*(x-Q)+R;
	if(type==2)return fabs(x-Q)+R;
	if(type==3)return exp(x-Q)+exp(Q-x);
	return cosh(P*(x-Q));
}
int main(){
	long long checks=0;
	mt19937 rng(5);
	type=0;
	assert(fabs(gss(-1000,1000)+5.0/3)<1e-5);
	checks++;
	for(int it=0;it<20000;it++){
		type=1+rng()%4;
		P=0.1+(rng()%1000)/100.0;
		Q=(int)(rng()%20001)/100.0-100;
		R=(int)(rng()%2001)-1000;
		double lo=Q-1-(rng()%1000)/10.0,hi=Q+1+(rng()%1000)/10.0;
		double x=gss(lo,hi);
		assert(fabs(x-Q)<1e-5);
		checks++;
		// 最小值在区间端点
		double y=gss(Q+1,Q+50);
		assert(fabs(y-(Q+1))<1e-5);
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
