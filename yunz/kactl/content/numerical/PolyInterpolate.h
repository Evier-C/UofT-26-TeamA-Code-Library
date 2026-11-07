/**
 * Description: 多项式插值 (牛顿插值): 给定 $n$ 个点 $(x_i, y_i)$, $x_i$ 互不相同,
 * 求唯一的不超过 $n-1$ 次的多项式 $p$ 使 $p(x_i) = y_i$.
 * 输入两个长为 $n$ 的 vector<double> (下标从 0 开始), 返回长为 $n$ 的系数
 * 数组 a, $p(x) = a_0 + a_1 x + \dots + a_{n-1} x^{n-1}$ (可用 Polynomial.h 的 peval 求值).
 * 浮点运算, $n$ 大时误差大; 可以自己选点时取 $x_k = c \cos(k \pi / (n-1))$ 更稳定.
 * 模素数下只求一个点的值请用拉格朗日插值公式, 不要用这个.
 * Usage: vector<double> x={0,1,2},y={1,2,5};
 * vector<double> a=interpolate(x,y); // a={1,0,1}
 * // 即 p(x)=1+x^2
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
