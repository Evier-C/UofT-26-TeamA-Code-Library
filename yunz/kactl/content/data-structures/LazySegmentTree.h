/**
 * Description: 通用懒标记线段树, 下标 [0, n), n >= 1. 换用途只改 T, U, f, g, h 和单位元,
 * 写法见下方懒标记写法. 默认: 区间加, 查区间和与最大值.
 * Usage: vector<T> a(n, {x, x, 1}); Seg s(a);
 * s.update(l, r, {v}); T q = s.query(l, r); // 都是 [l, r)
 * Time: O(\log N)
 */
#pragma once

struct T { ll sum, mx; int len; }; // 节点信息
struct U { ll add; };              // 懒标记
const T idT = {0, LLONG_MIN, 0};
const U idU = {0};
T f(T a, T b) {
	return {a.sum + b.sum, max(a.mx, b.mx), a.len + b.len};
}
T h(U u, T a) {
	return {a.sum + u.add * a.len, a.mx + u.add, a.len};
}
U g(U u, U v) { return {u.add + v.add}; } // 先 v 后 u

struct Seg {
	int n; vector<T> t; vector<U> d;
	Seg(const vector<T>& a) : n(sz(a)), t(4 * n), d(4 * n, idU) {
		build(1, 0, n, a);
	}
	void build(int x, int l, int r, const vector<T>& a) {
		if (r - l == 1) { t[x] = a[l]; return; }
		int m = (l + r) / 2;
		build(2 * x, l, m, a), build(2 * x + 1, m, r, a);
		t[x] = f(t[2 * x], t[2 * x + 1]);
	}
	void app(int x, U u) {
		t[x] = h(u, t[x]), d[x] = g(u, d[x]);
	}
	void push(int x) {
		app(2 * x, d[x]), app(2 * x + 1, d[x]), d[x] = idU;
	}
	void update(int L, int R, U u) { upd(L, R, u, 1, 0, n); }
	void upd(int L, int R, U u, int x, int l, int r) {
		if (R <= l || r <= L) return;
		if (L <= l && r <= R) return app(x, u);
		push(x);
		int m = (l + r) / 2;
		upd(L, R, u, 2 * x, l, m);
		upd(L, R, u, 2 * x + 1, m, r);
		t[x] = f(t[2 * x], t[2 * x + 1]);
	}
	T query(int L, int R) { return qry(L, R, 1, 0, n); }
	T qry(int L, int R, int x, int l, int r) {
		if (R <= l || r <= L) return idT;
		if (L <= l && r <= R) return t[x];
		push(x);
		int m = (l + r) / 2;
		return f(qry(L, R, 2 * x, l, m),
		         qry(L, R, 2 * x + 1, m, r));
	}
};
