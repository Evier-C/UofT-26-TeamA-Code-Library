/**
 * Description: FHQ treap (split/merge, no rotations). Node 0 is null.
 * Two modes sharing split/merge: an ordered multiset by value, or a sequence
 * by position with lazy reverse and range sum (b below holds [l, r)).
 * Don't mix reverse with value ops.
 * Usage: Treap T; T.insert(v); T.erase(v); T.rank(v); T.kth(k);
 * prev(v) = T.kth(T.rank(v) - 1), next(v) = T.kth(T.rank(v + 1));
 * T.rt = T.merge(T.rt, T.nn(v)); // append to sequence
 * int a, b, c; T.split(T.rt, l, a, b); T.split(b, r - l, b, c);
 * T.t[b].rev ^= 1; T.t[b].sum; T.rt = T.merge(T.merge(a, b), c);
 * Time: O(\log N) expected per operation
 */
#pragma once

struct Treap {
	struct N { int l, r, s; unsigned p; ll v, sum; bool rev; };
	vector<N> t{{0, 0, 0, 0, 0, 0, 0}};
	mt19937 rng{12345};
	int rt = 0;
	int nn(ll v) { // 新建节点
		t.push_back({0, 0, 1, (unsigned)rng(), v, v, 0});
		return sz(t) - 1;
	}
	void pull(int x) {
		N& n = t[x];
		n.s = t[n.l].s + t[n.r].s + 1;
		n.sum = t[n.l].sum + t[n.r].sum + n.v;
	}
	void push(int x) { // 下传翻转标记
		if (!t[x].rev) return;
		swap(t[x].l, t[x].r);
		t[t[x].l].rev ^= 1, t[t[x].r].rev ^= 1, t[x].rev = 0;
	}
	void split(int x, int k, int& a, int& b) { // 前 k 个给 a
		if (!x) { a = b = 0; return; }
		push(x);
		int ls = t[t[x].l].s;
		if (ls < k) split(t[x].r, k - ls - 1, t[x].r, b), a = x;
		else split(t[x].l, k, a, t[x].l), b = x;
		pull(x);
	}
	void splitv(int x, ll v, int& a, int& b) { // 值 < v 的给 a
		if (!x) { a = b = 0; return; }
		push(x);
		if (t[x].v < v) splitv(t[x].r, v, t[x].r, b), a = x;
		else splitv(t[x].l, v, a, t[x].l), b = x;
		pull(x);
	}
	int merge(int a, int b) { // a 的元素都在 b 前面
		if (!a || !b) return a ^ b;
		if (t[a].p > t[b].p) {
			push(a), t[a].r = merge(t[a].r, b), pull(a);
			return a;
		}
		push(b), t[b].l = merge(a, t[b].l), pull(b);
		return b;
	}
	void insert(ll v) {
		int n = nn(v), a, b;
		splitv(rt, v, a, b);
		rt = merge(merge(a, n), b);
	}
	void erase(ll v) { // 删除一个 v
		int a, b, c, d;
		splitv(rt, v, a, b), split(b, 1, c, d);
		rt = merge(a, c && t[c].v == v ? d : merge(c, d));
	}
	int rank(ll v) { // 严格小于 v 的个数
		int a, b;
		splitv(rt, v, a, b);
		int r = t[a].s;
		rt = merge(a, b);
		return r;
	}
	ll kth(int k) { // 第 k 小 (k 从 0 开始)
		for (int x = rt;;) {
			push(x);
			int ls = t[t[x].l].s;
			if (k == ls) return t[x].v;
			if (k < ls) x = t[x].l;
			else k -= ls + 1, x = t[x].r;
		}
	}
	void walk(int x, vector<ll>& o) { // 中序遍历
		if (!x) return;
		push(x), walk(t[x].l, o);
		o.push_back(t[x].v), walk(t[x].r, o);
	}
};
