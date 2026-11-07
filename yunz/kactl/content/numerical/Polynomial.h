/**
 * Description: 实系数多项式的基本操作. 多项式存成 vector<double> a, 下标从 0 开始,
 * $a[i]$ 为 $x^i$ 的系数, 次数为 a.size()-1.
 * \texttt{peval(a, x)}: 用秦九韶 (Horner) 法求 $p(x)$, 返回 double.
 * \texttt{pderiv(a)}: 原地求导, a 的长度减 1.
 * \texttt{pdivroot(a, x0)}: 原地除以 $(x - x_0)$ (综合除法), a 的长度减 1,
 * 余数 $p(x_0)$ 被丢弃, 所以 $x_0$ 应是根 (用于求出一个根后降次).
 * 注意 a 不能为空; 浮点误差随次数增大.
 * Usage: vector<double> a={2,-3,1}; // x^2-3x+2
 * double y=peval(a,0.5); // y=0.75
 * pdivroot(a,1); // 除以 x-1, a 变为 {-2,1}
 * pderiv(a); // a 变为 {1}
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
