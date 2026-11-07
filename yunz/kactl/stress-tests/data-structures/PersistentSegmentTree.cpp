#include "../utilities/template.h"

#include "../../content/data-structures/PersistentSegmentTree.h"

int main() {
	mt19937 rng(12345);
	auto rnd = [&](int lo, int hi) { return (int)(rng() % (hi - lo + 1)) + lo; };
	long long checks = 0;

	// 1) Random point-adds on random old versions vs brute-force copies.
	rep(it, 0, 3000) {
		int n = rnd(1, 40);
		PST t(n);
		vector<int> rt = {0};
		vector<vector<ll>> arr = {vector<ll>(n, 0)};
		rep(step, 0, 60) {
			int base = rnd(0, sz(rt) - 1), p = rnd(0, n - 1);
			ll v = rnd(-1000000, 1000000);
			rt.push_back(t.upd(rt[base], p, v));
			arr.push_back(arr[base]);
			arr.back()[p] += v;
			rep(q, 0, 5) { // query any version, old ones must be unchanged
				int ver = rnd(0, sz(rt) - 1);
				int l = rnd(0, n), r = rnd(0, n);
				if (l > r) swap(l, r);
				ll want = 0;
				rep(i, l, r) want += arr[ver][i];
				assert(t.query(rt[ver], l, r) == want);
				checks++;
			}
		}
		// every version, every range, at the end
		rep(ver, 0, sz(rt)) rep(l, 0, n + 1) rep(r, l, n + 1) {
			ll want = 0;
			rep(i, l, r) want += arr[ver][i];
			assert(t.query(rt[ver], l, r) == want);
			checks++;
		}
		// nodes created = O(log n) per update
		int depth = 1;
		while ((1 << (depth - 1)) < n) depth++;
		assert(sz(t.t) <= 1 + 60 * (depth + 1));
	}

	// 2) k-th smallest in a[l..r) (classic use) vs sorting.
	rep(it, 0, 2000) {
		int len = rnd(1, 50), V = rnd(1, 30);
		vi a(len);
		for (int& x : a) x = rnd(0, V - 1);
		PST t(V);
		vector<int> rt = {0};
		for (int x : a) rt.push_back(t.upd(rt.back(), x, 1));
		rep(l, 0, len) rep(r, l + 1, len + 1) {
			vi s(a.begin() + l, a.begin() + r);
			sort(all(s));
			rep(k, 0, r - l) {
				assert(t.kth(rt[l], rt[r], k) == s[k]);
				checks++;
			}
			assert(t.query(rt[r], 0, V) - t.query(rt[l], 0, V) == r - l);
		}
	}

	// 3) Large n, deep recursion sanity.
	{
		int n = 1000000000;
		PST t(n);
		vector<int> rt = {0};
		map<int, ll> m;
		rep(i, 0, 20000) {
			int p = rnd(0, n - 1); ll v = rnd(1, 1000);
			rt.push_back(t.upd(rt.back(), p, v));
			m[p] += v;
		}
		rep(q, 0, 2000) {
			int l = rnd(0, n - 1), r = rnd(l, n);
			ll want = 0;
			for (auto it2 = m.lower_bound(l); it2 != m.end() && it2->first < r; ++it2) want += it2->second;
			assert(t.query(rt.back(), l, r) == want);
			checks++;
		}
	}
	cout << "Tests passed! (" << checks << " checks)" << endl;
}
