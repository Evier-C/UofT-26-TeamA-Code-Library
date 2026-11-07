/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: 求覆盖区间 G 所需最少区间的下标集合。
 * 区间均为左闭右开。若要支持闭区间，将 (A) 处的条件加上 \texttt{|| R.empty()}。
 * 失败时（或 G 为空时）返回空集。
 * Usage: vector<pii> I; vi r = cover(pii(L, R), I);
 * // r 为所选区间在 I 中的下标 , 失败时为空
 * Time: O(N \log N)
 * Status: Tested on kattis:intervalcover
 */
#pragma once

template<class T>
vi cover(pair<T, T> G, vector<pair<T, T>> I) {
	vi S(sz(I)), R;
	iota(all(S), 0);
	sort(all(S), [&](int a, int b) { return I[a] < I[b]; });
	T cur = G.first;
	int at = 0;
	while (cur < G.second) { // (A)
		pair<T, int> mx = make_pair(cur, -1);
		while (at < sz(I) && I[S[at]].first <= cur) {
			mx = max(mx, make_pair(I[S[at]].second, S[at]));
			at++;
		}
		if (mx.second == -1) return {};
		cur = mx.first;
		R.push_back(mx.second);
	}
	return R;
}
