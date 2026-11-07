/**
 * Description: Li Chao tree on integer x in [lo, hi). Nodes are created on
 * demand, so any range works without compression. add inserts a line, or a
 * segment that only exists on [a, b). query returns the max at x, or LLONG\_MIN
 * if nothing covers x. For min, add $(-k, -m)$ and negate the answer.
 * Needs $|kx + m| < 9 \cdot 10^{18}$ and $C = hi - lo < 9 \cdot 10^{18}$.
 * Usage: LiChao lc(-1e9, 1e9 + 1);
 * lc.add({k, m}); lc.add({k, m}, a, b); lc.query(x);
 * Time: O(\log C) per line or query, O(\log^2 C) per segment
 */
#pragma once

struct LiChao {
	struct L {
		ll k, m;
		ll operator()(ll x) const { return k * x + m; }
	};
	struct N { L f{0, LLONG_MIN}; int c[2]{}; };
	vector<N> t; ll lo, hi;
	LiChao(ll lo, ll hi) : t(1), lo(lo), hi(hi) {}
	int ch(int x, int d) {
		if (!t[x].c[d]) t[x].c[d] = sz(t), t.emplace_back();
		return t[x].c[d];
	}
	void add(L f, ll a = LLONG_MIN, ll b = LLONG_MAX) {
		ins(0, lo, hi, a, b, f);
	}
	void ins(int x, ll l, ll r, ll a, ll b, L f) {
		if (b <= l || r <= a) return;
		ll m = l + (r - l) / 2;
		if (a <= l && r <= b) {
			if (f(m) > t[x].f(m)) swap(f, t[x].f);
			if (r - l == 1 || f.k == t[x].f.k) return;
			int d = f.k > t[x].f.k;
			ins(ch(x, d), d ? m : l, d ? r : m, a, b, f);
		} else {
			if (a < m) ins(ch(x, 0), l, m, a, b, f);
			if (b > m) ins(ch(x, 1), m, r, a, b, f);
		}
	}
	ll query(ll v) {
		ll res = LLONG_MIN, l = lo, r = hi;
		for (int x = 0;;) {
			res = max(res, t[x].f(v));
			ll m = l + (r - l) / 2;
			int d = v >= m;
			if (!t[x].c[d]) return res;
			x = t[x].c[d];
			(d ? l : r) = m;
		}
	}
};
