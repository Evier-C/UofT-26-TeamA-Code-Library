/**
 * Description: 黄金分割搜索: 求单峰函数 $f$ 在 $[a, b]$ 上的最小值点 ($f$ 先降后升).
 * 误差约 eps $= 10^{-7}$. 整数自变量见 Various 章 TernarySearch.h.
 * Usage: double f(double x){return 4+x+.3*x*x;} // 全局函数, 自己写
 * double xm=gss(-1000,1000); // 最小值点, 约为 -5/3
 * double ym=f(xm); // 最小值
 * // 求最大值: 把代码中的 f1<f2 改成 f1>f2
 * Time: O(\log((b-a) / \epsilon))
 */
#pragma once

double f(double x); // 要最小化的函数, 在别处自己实现
double gss(double a,double b){
	// r 要足够精确, 才能保证 a < x1 < x2 < b
	double r=(sqrt(5.0)-1)/2;
	double eps=1e-7;
	double x1=b-r*(b-a);
	double x2=a+r*(b-a);
	double f1=f(x1);
	double f2=f(x2);
	while(b-a>eps){
		if(f1<f2){ // 求最大值改为 f1 > f2
			b=x2;
			x2=x1;
			f2=f1;
			x1=b-r*(b-a);
			f1=f(x1);
		}else{
			a=x1;
			x1=x2;
			f1=f2;
			x2=a+r*(b-a);
			f2=f(x2);
		}
	}
	return a;
}
