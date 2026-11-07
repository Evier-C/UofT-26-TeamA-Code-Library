/**
 * Author: Simon Lindholm
 * License: CC0
 * Description: 在一组互不相交的区间中添加或删除区间。
 * 添加时会与集合中所有重叠的区间合并。区间均为左闭右开 $[L, R)$。
 * Usage: set<pii> is; auto it = addInterval(is, L, R);
 * removeInterval(is, L, R); // it 指向合并后的区间
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

set<pii>::iterator addInterval(set<pii>& is, int L, int R) {
	if (L == R) return is.end();
	auto it = is.lower_bound({L, R}), before = it;
	while (it != is.end() && it->first <= R) {
		R = max(R, it->second);
		before = it = is.erase(it);
	}
	if (it != is.begin() && (--it)->second >= L) {
		L = min(L, it->first);
		R = max(R, it->second);
		is.erase(it);
	}
	return is.insert(before, {L,R});
}

void removeInterval(set<pii>& is, int L, int R) {
	if (L == R) return;
	auto it = addInterval(is, L, R);
	auto r2 = it->second;
	if (it->first == L) is.erase(it);
	else (int&)it->second = L;
	if (R != r2) is.emplace(R, r2);
}
