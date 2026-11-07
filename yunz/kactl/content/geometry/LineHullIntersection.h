/**
 * Author: Oleksandr Bacherikov, chilli
 * Date: 2019-05-07
 * License: Boost Software License
 * Source: https://github.com/AlCash07/ACTL/blob/master/include/actl/geometry/algorithm/intersect/line_convex_polygon.hpp
 * Description: 直线与凸多边形求交. 多边形须为逆时针且无共线点.
 * lineHull(a, b, poly) 返回一对下标, 描述直线 ab 与多边形的相交情况:
 *  \begin{itemize*}
 *    \item $(-1, -1)$ 不相交,
 *    \item $(i, -1)$ 只碰到顶点 $i$,
 *    \item $(i, i)$ 沿着边 $(i, i+1)$,
 *    \item $(i, j)$ 穿过边 $(i, i+1)$ 和 $(j, j+1)$.
 *  \end{itemize*}
 *  最后一种情形中若穿过顶点 $i$, 视为发生在边 $(i, i+1)$ 上.
 *  返回顺序与直线依次碰到多边形的顺序一致.
 * \texttt{extrVertex} 返回凸包上在方向 dir 上投影最大的顶点下标.
 * Usage:
 * 	array<int, 2> r = lineHull(a, b, poly);
 * 	int i = extrVertex(poly, dir); // dir 方向上最远的顶点
 * Time: O(\log n)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

#define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
template <class P> int extrVertex(vector<P>& poly, P dir) {
	int n = sz(poly), lo = 0, hi = n;
	if (extr(0)) return 0;
	while (lo + 1 < hi) {
		int m = (lo + hi) / 2;
		if (extr(m)) return m;
		int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
		(ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
	}
	return lo;
}

#define cmpL(i) sgn(a.cross(poly[i], b))
template <class P>
array<int, 2> lineHull(P a, P b, vector<P>& poly) {
	int endA = extrVertex(poly, (a - b).perp());
	int endB = extrVertex(poly, (b - a).perp());
	if (cmpL(endA) < 0 || cmpL(endB) > 0)
		return {-1, -1};
	array<int, 2> res;
	rep(i,0,2) {
		int lo = endB, hi = endA, n = sz(poly);
		while ((lo + 1) % n != hi) {
			int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
			(cmpL(m) == cmpL(endB) ? lo : hi) = m;
		}
		res[i] = (lo + !cmpL(hi)) % n;
		swap(endA, endB);
	}
	if (res[0] == res[1]) return {res[0], -1};
	if (!cmpL(res[0]) && !cmpL(res[1]))
		switch ((res[0] - res[1] + sz(poly) + 1) % sz(poly)) {
			case 0: return {res[0], res[0]};
			case 2: return {res[1], res[1]};
		}
	return res;
}
