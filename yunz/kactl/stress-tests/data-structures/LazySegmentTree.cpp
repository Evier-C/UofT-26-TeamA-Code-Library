#include "../utilities/template.h"

#include "../../content/data-structures/LazySegmentTree.h"

int main() {
	mt19937 rng(9);
	auto rnd = [&](int lo, int hi) { return lo + (int)(rng() % (unsigned)(hi - lo + 1)); };
	long long checks = 0;
	rep(it, 0, 3000) {
		int n = rnd(1, 50);
		vector<ll> a(n);
		vector<T> in(n);
		rep(i, 0, n) a[i] = rnd(-1000, 1000), in[i] = {a[i], a[i], 1};
		Seg s(in);
		rep(step, 0, 150) {
			int l = rnd(0, n - 1), r = rnd(l + 1, n);
			if (rng() % 2) {
				ll v = rnd(-1000, 1000);
				s.update(l, r, {v});
				rep(i, l, r) a[i] += v;
			} else {
				T q = s.query(l, r);
				ll sm = 0, mx = LLONG_MIN;
				rep(i, l, r) sm += a[i], mx = max(mx, a[i]);
				assert(q.sum == sm && q.mx == mx && q.len == r - l);
				checks++;
			}
		}
	}
	cout << "Tests passed! (" << checks << " checks)" << endl;
}
