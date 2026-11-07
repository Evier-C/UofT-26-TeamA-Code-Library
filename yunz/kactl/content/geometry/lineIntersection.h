/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
若过 s1,e1 的直线与过 s2,e2 的直线有唯一交点, 返回 \{1, 交点\};
无交点 (平行) 返回 \{0, (0,0)\}; 有无穷多交点 (重合) 返回 \{-1, (0,0)\}.
若 P 为 Point<ll> 而交点不是整点, 结果错误.
中间有三个坐标的乘积, 用 int 或 ll 时注意溢出.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}
 * Usage:
 * 	auto res = lineInter(s1,e1,s2,e2);
 * 	if (res.first == 1) // 交点为 res.second
 * 		cout << res.second << endl;
 * Status: stress-tested, and tested through half-plane tests
 */
#pragma once

#include "Point.h"

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // 平行
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}
