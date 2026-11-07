/**
 * Author: Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Floyd–Warshall_algorithm
 * Description: 有向图全源最短路, 允许负边权.
 * 输入距离矩阵 $m$, 若 $i$ 与 $j$ 不相邻则 $m[i][j] = \texttt{inf}$.
 * 结束后 $m[i][j]$ 为 $i$ 到 $j$ 的最短距离, 无路径时为 \texttt{inf},
 * 路径经过负环时为 \texttt{-inf}.
 * Usage: vector<vector<ll>> m(n, vector<ll>(n, inf));
 * m[a][b] = min(m[a][b], w); floydWarshall(m);
 * Time: O(N^3)
 * Status: slightly tested
 */
#pragma once

const ll inf = 1LL << 62;
void floydWarshall(vector<vector<ll>>& m) {
	int n = sz(m);
	rep(i,0,n) m[i][i] = min(m[i][i], 0LL);
	rep(k,0,n) rep(i,0,n) rep(j,0,n)
		if (m[i][k] != inf && m[k][j] != inf) {
			auto newDist = max(m[i][k] + m[k][j], -inf);
			m[i][j] = min(m[i][j], newDist);
		}
	rep(k,0,n) if (m[k][k] < 0) rep(i,0,n) rep(j,0,n)
		if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
}
