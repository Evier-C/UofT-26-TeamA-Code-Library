/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: 若 p 在多边形内则返回 true. strict 为 true 时,
 * 边界上的点返回 false. 中间有乘积, 注意溢出.
 * Time: O(n)
 * Usage:
 * vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
 * bool in = inPolygon(v, P{3, 3}, false); // 含边界
 * Status: stress-tested and tested on kattis:pointinpolygon
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"
#include "SegmentDistance.h"

template<class P> // 顺时针或逆时针多边形均可
bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = sz(p);
	rep(i,0,n) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		// 浮点数时可改用下一行
		//if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}
