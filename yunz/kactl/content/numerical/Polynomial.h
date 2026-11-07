/**
 * Author: David Rydh, Per Austrin
 * Date: 2003-03-16
 * Description: 实系数多项式, $a[i]$ 为 $x^i$ 的系数. \texttt{p(x)} 用 Horner 法求值;
 * \texttt{diff()} 原地求导; \texttt{divroot(x0)} 原地除以 $(x - x_0)$ (余数丢弃, $x_0$ 应为根).
 * Usage: Poly p{{2,-3,1}}; // a[i] 为 x^i 的系数
 * double y = p(0.5); p.divroot(1); // 除以 (x - 1)
 * p.diff(); // 原地求导
 */
#pragma once

struct Poly {
	vector<double> a;
	double operator()(double x) const {
		double val = 0;
		for (int i = sz(a); i--;) (val *= x) += a[i];
		return val;
	}
	void diff() {
		rep(i,1,sz(a)) a[i-1] = i*a[i];
		a.pop_back();
	}
	void divroot(double x0) {
		double b = a.back(), c; a.back() = 0;
		for(int i=sz(a)-1; i--;) c = a[i], a[i] = a[i+1]*x0+b, b=c;
		a.pop_back();
	}
};
