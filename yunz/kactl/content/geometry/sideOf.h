/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: 返回从 $s$ 看向 $e$ 时 $p$ 所在的位置. 1/0/-1 $\Leftrightarrow$ 左侧/在直线上/右侧.
 * 若给出可选参数 $eps$, 则 $p$ 到直线距离不超过 $eps$ 时返回 0.
 * P 应为 Point<T>, T 如 double 或 long long.
 * 中间有乘积, 用 int 或 long long 时注意溢出.
 * Usage:
 * 	bool left = sideOf(p1,p2,q)==1; // q 在 p1 到 p2 的左侧
 * Status: tested
 */
#pragma once

#include "Point.h"

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
	auto a = (e-s).cross(p-s);
	double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}
