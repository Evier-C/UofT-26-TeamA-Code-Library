/**
 * Author: Simon Lindholm
 * Date: 2015-03-20
 * License: CC0
 * Source: me
 * Description: 将 [from, to) 上的单调函数划分为最少的若干半开区间，使函数在每个区间上取值相同。
 *  对每个这样的区间调用回调 g。
 * Usage: auto f = [\&](int x) { return v[x]; };
 * auto g = [\&](int lo, int hi, T val) { ... };
 * constantIntervals(0, sz(v), f, g);
 * // 对每段 [lo, hi) 调用 g, 段内 f 的值均为 val
 * Time: O(k\log\frac{n}{k})
 * Status: tested
 */
#pragma once

template<class F, class G, class T>
void rec(int from, int to, F& f, G& g, int& i, T& p, T q) {
	if (p == q) return;
	if (from == to) {
		g(i, to, p);
		i = to; p = q;
	} else {
		int mid = (from + to) >> 1;
		rec(from, mid, f, g, i, p, f(mid));
		rec(mid+1, to, f, g, i, p, q);
	}
}
template<class F, class G>
void constantIntervals(int from, int to, F f, G g) {
	if (to <= from) return;
	int i = from; auto p = f(i), q = f(to-1);
	rec(from, to-1, f, g, i, p, q);
	g(i, to, q);
}
