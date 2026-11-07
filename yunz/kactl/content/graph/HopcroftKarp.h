/**
 * Author: Adam Soltan
 * Date: 2026-01-13
 * License: CC0
 * Description: 快速二分图匹配. $g$ 为左部各点的邻接表 (存右部点编号),
 * $r$ 为长度等于右部点数且全为 $-1$ 的数组. 返回匹配数.
 * $r[i]$ 为右部点 $i$ 匹配的左部点, 未匹配为 $-1$.
 * Usage 中的 $l[i]$ 为左部点 $i$ 匹配的右部点.
 * Usage: vi r(m, -1); hopcroftKarp(g, r);
 * vi l(sz(g), -1); rep(j,0,m) if (r[j] != -1) l[r[j]] = j;
 * Time: O(E \sqrt{V})
 * Status: stress-tested by MinimumVertexCover and tested on Library Checker
 */
#pragma once

int hopcroftKarp(vector<vi>& g, vi& r) {
	int n = sz(g), res = 0;
	vi l(n, -1), q(n), d(n);
	auto dfs = [&](auto f, int u) -> bool {
		int t = exchange(d[u], 0) + 1;
		for (int v : g[u])
			if (r[v] == -1 || (d[r[v]] == t && f(f, r[v])))
				return l[u] = v, r[v] = u, 1;
		return 0;
	};
	for (int t = 0, f = 0;; t = f = 0, d.assign(n, 0)) {
		rep(i,0,n) if (l[i] == -1) q[t++] = i, d[i] = 1;
		rep(i,0,t) for (int v : g[q[i]]) {
			if (r[v] == -1) f = 1;
			else if (!d[r[v]]) d[r[v]] = d[q[i]] + 1, q[t++] = r[v];
		}
		if (!f) return res;
		rep(i,0,n) if (l[i] == -1) res += dfs(dfs, i);
	}
}
