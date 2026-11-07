/**
 * Description: Point update, range query on [0, n). upd returns a new root;
 * old roots stay valid. Root 0 is the empty tree. Change T, f, unit as needed.
 * kth needs f = + and version i holding the counts of a[0..i).
 * Usage: PST t(n); vi rt = {0};
 * rt.push_back(t.upd(rt.back(), p, v)); // a[p] = f(a[p], v)
 * t.query(rt[i], l, r); // f over [l, r) in version i
 * t.kth(rt[l], rt[r], k); // k-th (0-indexed) smallest value in a[l..r)
 * Time: O(\log N)
 */
#pragma once

struct PST {
	typedef ll T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; }
	struct N { T v; int l, r; };
	vector<N> t = {{unit, 0, 0}}; int n;
	PST(int n) : n(n) {}
	int upd(int x, int p, T v, int l = 0, int r = -1) {
		if (r < 0) r = n;
		N c = t[x];
		if (r - l == 1) c.v = f(c.v, v);
		else {
			int m = (l + r) / 2;
			if (p < m) c.l = upd(c.l, p, v, l, m);
			else c.r = upd(c.r, p, v, m, r);
			c.v = f(t[c.l].v, t[c.r].v);
		}
		t.push_back(c);
		return sz(t) - 1;
	}
	T query(int x, int b, int e, int l = 0, int r = -1) {
		if (r < 0) r = n;
		if (!x || e <= l || r <= b) return unit;
		if (b <= l && r <= e) return t[x].v;
		int m = (l + r) / 2;
		return f(query(t[x].l, b, e, l, m), query(t[x].r, b, e, m, r));
	}
	int kth(int a, int b, T k, int l = 0, int r = -1) {
		if (r < 0) r = n;
		if (r - l == 1) return l;
		int m = (l + r) / 2;
		T c = t[t[b].l].v - t[t[a].l].v;
		if (k < c) return kth(t[a].l, t[b].l, k, l, m);
		return kth(t[a].r, t[b].r, k - c, m, r);
	}
};
