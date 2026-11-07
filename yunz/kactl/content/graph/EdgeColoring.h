/**
 * Author: Simon Lindholm
 * Date: 2020-10-12
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Misra_%26_Gries_edge_coloring_algorithm
 * https://codeforces.com/blog/entry/75431 for the note about bipartite graphs.
 * Description: 给定最大度为 $D$ 的简单无向图, 求边的 $(D + 1)$ 染色,
 * 使相邻的边颜色不同. ($D$ 染色是 NP-hard 的, 但二分图可以通过
 * 反复对最大度的点求匹配做到.)
 * Usage: vector<pii> eds; // 边 (u, v), 点编号 0..N-1
 * vi col = edgeColoring(N, eds); // col[i] 为边 i 的颜色
 * Time: O(NM)
 * Status: stress-tested, tested on kattis:gamescheduling
 */
#pragma once

vi edgeColoring(int N, vector<pii> eds) {
	vi cc(N + 1), ret(sz(eds)), fan(N), free(N), loc;
	for (pii e : eds) ++cc[e.first], ++cc[e.second];
	int u, v, ncols = *max_element(all(cc)) + 1;
	vector<vi> adj(N, vi(ncols, -1));
	for (pii e : eds) {
		tie(u, v) = e;
		fan[0] = v;
		loc.assign(ncols, 0);
		int at = u, end = u, d, c = free[u], ind = 0, i = 0;
		while (d = free[v], !loc[d] && (v = adj[u][d]) != -1)
			loc[d] = ++ind, cc[ind] = d, fan[ind] = v;
		cc[loc[d]] = c;
		for (int cd = d; at != -1; cd ^= c ^ d, at = adj[at][cd])
			swap(adj[at][cd], adj[end = at][cd ^ c ^ d]);
		while (adj[fan[i]][d] != -1) {
			int left = fan[i], right = fan[++i], e = cc[i];
			adj[u][e] = left;
			adj[left][e] = u;
			adj[right][e] = -1;
			free[right] = e;
		}
		adj[u][d] = fan[i];
		adj[fan[i]][d] = u;
		for (int y : {fan[0], u, end})
			for (int& z = free[y] = 0; adj[y][z] != -1; z++);
	}
	rep(i,0,sz(eds))
		for (tie(u, v) = eds[i]; adj[u][ret[i]] != v;) ++ret[i];
	return ret;
}
