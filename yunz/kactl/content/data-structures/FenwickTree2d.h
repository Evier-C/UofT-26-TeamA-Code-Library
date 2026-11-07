/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: 二维树状数组: 求所有 $i < I, j < J$ 的 a[i,j] 之和, 单点增加 a[i,j].
 * 要求事先知道所有要修改的位置 (先对它们调用 fakeUpdate(), 再 init()).
 * Usage: FT2 f(X); f.fakeUpdate(x, y); // 先登记所有修改点
 * f.init(); f.update(x, y, d); f.query(I, J);
 * Time: $O(\log^2 N)$. (用可持久化线段树可做到 $O(\log N)$.)
 * Status: stress-tested
 */
#pragma once

#include "FenwickTree.h"

struct FT2 {
	vector<vi> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < sz(ys); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (vi& v : ys) sort(all(v)), ft.emplace_back(sz(v));
	}
	int ind(int x, int y) {
		return (int)(lower_bound(all(ys[x]), y) - ys[x].begin()); }
	void update(int x, int y, ll dif) {
		for (; x < sz(ys); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
};
