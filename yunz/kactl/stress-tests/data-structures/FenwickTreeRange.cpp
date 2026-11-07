#include "../utilities/template.h"

#include "../../content/data-structures/FenwickTree.h"

int main() {
	mt19937 rng(5);
	auto rnd = [&](int lo, int hi) { return lo + (int)(rng() % (unsigned)(hi - lo + 1)); };
	long long checks = 0;
	rep(it, 0, 3000) {
		int n = rnd(1, 50);
		RFT f(n);
		vector<ll> a(n);
		rep(step, 0, 200) {
			int l = rnd(0, n), r = rnd(0, n);
			if (l > r) swap(l, r);
			if (rng() % 2) {
				ll v = rnd(-1000000000, 1000000000);
				f.add(l, r, v);
				rep(i, l, r) a[i] += v;
			} else {
				ll want = 0;
				rep(i, l, r) want += a[i];
				assert(f.query(l, r) == want);
				checks++;
			}
		}
		rep(l, 0, n + 1) rep(r, l, n + 1) {
			assert(f.query(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
			checks++;
		}
	}
	cout << "Tests passed! (" << checks << " checks)" << endl;
}
