/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: 求二分图 (A, B) 的最小点覆盖, $|A| = n$, $|B| = m$.
 *  $g$ 为左部各点的邻接表.
 *  覆盖的大小等于最大匹配数, 其补集是最大独立集.
 * Usage: vi c = cover(g, n, m); // 右部点 j 记为 n + j
 * Status: stress-tested
 */
#pragma once

#include "HopcroftKarp.h"

vi cover(vector<vi>& g, int n, int m) {
	vi match(m, -1);
	int res = hopcroftKarp(g, match);
	vector<bool> lfound(n, true), seen(m);
	for (int it : match) if (it != -1) lfound[it] = false;
	vi q, cover;
	rep(i,0,n) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		for (int e : g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.push_back(match[e]);
		}
	}
	rep(i,0,n) if (!lfound[i]) cover.push_back(i);
	rep(i,0,m) if (seen[i]) cover.push_back(n+i);
	assert(sz(cover) == res);
	return cover;
}
