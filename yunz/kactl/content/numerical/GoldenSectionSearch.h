/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-17
 * License: CC0
 * Source: Numeriska algoritmer med matlab, Gerd Eriksson, NADA, KTH
 * Description: 在区间 $[a,b]$ 上求使函数 $f$ 取最小值的自变量, 要求 $f$ 在该区间上单峰,
 * 即只有一个局部极小值且没有局部极大值. 结果的最大误差为 $eps$. 稍改代码即可同样
 * 用于求最大值. 离散版本见 Various 章的 TernarySearch.h.
 * Usage:
	double func(double x) { return 4+x+.3*x*x; }
	double xmin = gss(-1000,1000,func); // 最小值点
 * Time: O(\log((b-a) / \epsilon))
 * Status: tested
 */
#pragma once

/// r 必须足够精确, 否则不一定能保持 a < x1 < x2 < b.
double gss(double a,double b,double(*f)(double)){
	double r=(sqrt(5)-1)/2,eps=1e-7;
	double x1=b-r*(b-a),x2=a+r*(b-a);
	double f1=f(x1),f2=f(x2);
	while(b-a>eps)
		if(f1<f2){ // 求最大值则改为 >
			b=x2;x2=x1;f2=f1;
			x1=b-r*(b-a);f1=f(x1);
		}else{
			a=x1;x1=x2;f1=f2;
			x2=a+r*(b-a);f2=f(x2);
		}
	return a;
}
