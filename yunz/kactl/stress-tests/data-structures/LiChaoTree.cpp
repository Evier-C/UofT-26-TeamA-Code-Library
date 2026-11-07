#include "../utilities/template.h"

#include "../../content/data-structures/LiChaoTree.h"
namespace lc2 {
#include "../../content/data-structures/LineContainer.h"
}

struct Seg { ll k, m, a, b; };

ll brute(const vector<Seg>& v, ll x) {
	ll r = LLONG_MIN;
	for (auto& s : v) if (s.a <= x && x < s.b) r = max(r, s.k * x + s.m);
	return r;
}

int main() {
	mt19937_64 rng(7);
	auto rnd = [&](ll lo, ll hi) { return lo + (ll)(rng() % (unsigned long long)(hi - lo + 1)); };
	long long checks = 0;

	rep(it, 0, 4000) {
		ll lo = rnd(-30, 10), hi = lo + rnd(1, 40);
		LiChao t(lo, hi);
		vector<Seg> v;
		rep(step, 0, 40) {
			ll k = rnd(-20, 20), m = rnd(-200, 200);
			if (rng() % 2) {
				t.add({k, m});
				v.push_back({k, m, LLONG_MIN, LLONG_MAX});
			} else {
				ll a = rnd(lo - 5, hi + 5), b = rnd(lo - 5, hi + 5);
				if (a > b) swap(a, b);
				t.add({k, m}, a, b);
				v.push_back({k, m, a, b});
			}
			for (ll x = lo; x < hi; x++) {
				assert(t.query(x) == brute(v, x));
				checks++;
			}
		}
	}

	rep(it, 0, 300) {
		ll lo = -1000000000, hi = 1000000001;
		LiChao t(lo, hi);
		lc2::LineContainer hull;
		vector<Seg> v;
		rep(step, 0, 300) {
			ll k = rnd(-1000000, 1000000), m = rnd(-(ll)1e15, (ll)1e15);
			if (step % 3 == 2) {
				ll a = rnd(lo, hi), b = rnd(lo, hi);
				if (a > b) swap(a, b);
				t.add({k, m}, a, b);
				v.push_back({k, m, a, b});
			} else {
				t.add({k, m});
				v.push_back({k, m, LLONG_MIN, LLONG_MAX});
			}
			rep(q, 0, 5) {
				ll x = rnd(lo, hi - 1);
				assert(t.query(x) == brute(v, x));
				checks++;
			}
		}
		LiChao t2(lo, hi);
		vector<Seg> w;
		rep(step, 0, 300) {
			ll k = rnd(-1000000, 1000000), m = rnd(-(ll)1e15, (ll)1e15);
			t2.add({k, m}); hull.add(k, m); w.push_back({k, m, LLONG_MIN, LLONG_MAX});
			ll x = rnd(lo, hi - 1);
			assert(t2.query(x) == hull.query(x));
			checks++;
		}
	}

	{
		LiChao mn(-50, 50);
		vector<Seg> v;
		rep(step, 0, 200) {
			ll k = rnd(-9, 9), m = rnd(-99, 99);
			mn.add({-k, -m});
			v.push_back({k, m, LLONG_MIN, LLONG_MAX});
			for (ll x = -50; x < 50; x++) {
				ll want = LLONG_MAX;
				for (auto& s : v) want = min(want, s.k * x + s.m);
				assert(-mn.query(x) == want);
				checks++;
			}
		}
	}

	{
		int n = 200000;
		LiChao t(-1000000000, 1000000001);
		rep(i, 0, n) t.add({rnd(-1000000, 1000000), rnd(-(ll)1e15, (ll)1e15)});
		assert(sz(t.t) <= 1 + n * 32);
		ll s = 0;
		rep(i, 0, n) s ^= t.query(rnd(-1000000000, 1000000000));
		cout << "nodes for " << n << " lines: " << sz(t.t) << " (xor " << (s & 7) << ")" << endl;
	}
	cout << "Tests passed! (" << checks << " checks)" << endl;
}
