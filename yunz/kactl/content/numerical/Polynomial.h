/**
 * Description: 实系数多项式, 下标从 0 开始, $a[i]$ 为 $x^i$ 的系数.
 * peval 用秦九韶 (Horner) 法求值; pderiv 原地求导;
 * pdivroot 原地除以 $(x-x_0)$, 余数丢弃 ($x_0$ 应为根).
 * Usage: vector<double> a={2,-3,1}; // x^2-3x+2
 * double y=peval(a,0.5); // 0.75
 * pdivroot(a,1); // a 变为 {-2,1}, 即 x-2
 * pderiv(a); // a 变为 {1}
 * Time: 均为 O(n)
 */
#pragma once

double peval(const vector<double>&a,double x){
	double res=0;
	for(int i=(int)a.size()-1;i>=0;i--)res=res*x+a[i];
	return res;
}
void pderiv(vector<double>&a){ // 求导, 次数减 1
	for(int i=1;i<(int)a.size();i++)a[i-1]=i*a[i];
	a.pop_back();
}
void pdivroot(vector<double>&a,double x0){ // 综合除法
	double b=a.back(),c;
	a.back()=0;
	for(int i=(int)a.size()-2;i>=0;i--)
		c=a[i],a[i]=a[i+1]*x0+b,b=c;
	a.pop_back();
}
