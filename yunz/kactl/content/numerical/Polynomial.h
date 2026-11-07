/**
 * Description: 实系数多项式求值, 求导, 除以 $(x - x_0)$. 系数下标从 0 开始, a 不能为空.
 * pdivroot 丢弃余数, 所以 $x_0$ 应是根 (求出一个根后降次).
 * Usage: vector<double> a={2,-3,1}; // a[i] 为 x^i 的系数
 * double y=peval(a,0.5); // p(0.5)=0.75
 * pdivroot(a,1); // 原地除以 x-1, a 变为 {-2,1}
 * pderiv(a); // 原地求导, a 变为 {1}
 * Time: 均为 O(n), $n$ 为次数
 */
#pragma once

double peval(const vector<double>&a,double x){
	double res=0;
	for(int i=(int)a.size()-1;i>=0;i--){
		res=res*x+a[i];
	}
	return res;
}
void pderiv(vector<double>&a){
	for(int i=1;i<(int)a.size();i++){
		a[i-1]=i*a[i];
	}
	a.pop_back();
}
void pdivroot(vector<double>&a,double x0){
	double b=a.back();
	a.back()=0;
	for(int i=(int)a.size()-2;i>=0;i--){
		double c=a[i];
		a[i]=a[i+1]*x0+b;
		b=c;
	}
	a.pop_back();
}
