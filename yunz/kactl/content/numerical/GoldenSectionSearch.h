/**
 * Description: 黄金分割搜索: 在 $[a,b]$ 上求单峰函数 $f$ 的最小值点
 * (只有一个局部极小值, 没有局部极大值), 误差约 eps. 求最大值把
 * $f_1 < f_2$ 改成 $f_1 > f_2$. 每次只算一次 $f$, 比三分快.
 * 离散版本见 Various 章 TernarySearch.h.
 * Usage: double f(double x){return 4+x+.3*x*x;} // 自己写 f
 * double xm=gss(-1000,1000); // xm 约为 -5/3
 * Time: O(\log((b-a) / \epsilon))
 */
#pragma once

double f(double x); // 要最小化的函数, 在别处自己实现
double gss(double a,double b){
	// r 要足够精确, 才能保证 a < x1 < x2 < b
	double r=(sqrt(5.0)-1)/2,eps=1e-7;
	double x1=b-r*(b-a),x2=a+r*(b-a);
	double f1=f(x1),f2=f(x2);
	while(b-a>eps)
		if(f1<f2){ // 求最大值改为 f1 > f2
			b=x2;x2=x1;f2=f1;
			x1=b-r*(b-a);f1=f(x1);
		}else{
			a=x1;x1=x2;f1=f2;
			x2=a+r*(b-a);f2=f(x2);
		}
	return a;
}
