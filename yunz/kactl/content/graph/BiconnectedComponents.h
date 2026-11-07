/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: 求无向图的所有点双连通分量, 并对每个分量的边集调用回调.
 *  同一点双内任意两点之间至少有两条内部不相交的路径 (即存在经过它们的环).
 *  一个点可以属于多个分量. 不属于任何分量的边是桥, 即不在任何环上.
 * Usage:
 *  int eid = 0; ed.resize(N); for (auto \&x: ed) x.clear();
 *  for (auto [a, b] : edges) { // 对每条边
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& edgelist) {...}); // 分量的边编号
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 */
#pragma once

vi num, st;
vector<vector<pii>> ed;
int Time;
template<class F>
int dfs(int at, int par, F& f) {
	int me = num[at] = ++Time, top = me;
	for (auto [y, e] : ed[at]) if (e != par) {
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me)
				st.push_back(e);
		} else {
			int si = sz(st);
			int up = dfs(y, e, f);
			top = min(top, up);
			if (up == me) {
				st.push_back(e);
				f(vi(st.begin() + si, st.end()));
				st.resize(si);
			}
			else if (up < me) st.push_back(e);
			else { /* e 是桥 */ }
		}
	}
	return top;
}

template<class F>
void bicomps(F f) {
	num.assign(sz(ed), 0);
	rep(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
}
