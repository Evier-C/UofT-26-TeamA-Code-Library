/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: 求解 2-SAT: 给布尔变量 a, b, c, ... 赋值, 使形如
 * $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$ 的表达式为真, 或报告无解.
 * 取反的变量用按位取反表示 (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(n); // n 为布尔变量个数
 *  ts.either(0, \tilde3); // 变量 0 为真或变量 3 为假
 *  ts.setValue(2); // 变量 2 为真
 *  ts.atMostOne({0,\tilde1,2}); // 0 , \tilde1 , 2 中至多一个为真
 *  ts.solve(); // 有解时返回 true
 *  ts.values[0..N-1] 为各变量的赋值
 * Time: O(N+E), 其中 N 为布尔变量个数, E 为子句个数.
 * Status: stress-tested
 */
#pragma once

struct TwoSat {
	int N;
	vector<vi> gr;
	vi values; // 0 为假 ; 1 为真

	TwoSat(int n = 0) : N(n), gr(2*n) {}

	int addVar() { // 可选
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}

	void either(int f, int j) {
		f = max(2*f, -1-2*f);
		j = max(2*j, -1-2*j);
		gr[f].push_back(j^1);
		gr[j].push_back(f^1);
	}
	void setValue(int x) { either(x, x); }

	void atMostOne(const vi& li) { // 可选
		if (sz(li) <= 1) return;
		int cur = ~li[0];
		rep(i,2,sz(li)) {
			int next = addVar();
			either(cur, ~li[i]);
			either(cur, next);
			either(~li[i], next);
			cur = ~next;
		}
		either(cur, ~li[1]);
	}

	vi val, comp, z; int time = 0;
	int dfs(int i) {
		int low = val[i] = ++time, x; z.push_back(i);
		for(int e : gr[i]) if (!comp[e])
			low = min(low, val[e] ?: dfs(e));
		if (low == val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = low;
			if (values[x>>1] == -1)
				values[x>>1] = x&1;
		} while (x != i);
		return val[i] = low;
	}

	bool solve() {
		values.assign(N, -1);
		val.assign(2*N, 0); comp = val;
		rep(i,0,2*N) if (!comp[i]) dfs(i);
		rep(i,0,N) if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};
