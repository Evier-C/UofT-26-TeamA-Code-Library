/**
 * Description: 实数多项式插值: 由 $n$ 个点 ($x_i$ 互不相同) 求不超过 $n-1$ 次多项式的系数.
 * 浮点运算, $n$ 大时误差大; 能自己选点时取 $x_k = c \cos(k \pi / (n-1))$.
 * 模素数下求单点值用 LagrangeInterp.
 * Usage: vector<double> x={0,1,2},y={1,2,5}; // n 个点
 * vector<double> a=interpolate(x,y); // a={1,0,1}
 * // a[i] 为 x^i 的系数, 即 p(x)=1+x^2
 * Time: O(n^2)
 */
#pragma once

vector<double>interpolate(vector<double>x,vector<double>y){
	int n=x.size();
	vector<double>res(n),tmp(n);
	// 均差: 结束后 y[k] 为 f[x_0..x_k]
	for(int k=0;k<n-1;k++){
		for(int i=k+1;i<n;i++){
			y[i]=(y[i]-y[k])/(x[i]-x[k]);
		}
	}
	// tmp 为 (x-x_0)...(x-x_{k-1}) 的系数
	double last=0;
	tmp[0]=1;
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			res[i]+=y[k]*tmp[i];
			swap(last,tmp[i]);
			tmp[i]-=last*x[k];
		}
	}
	return res;
}
