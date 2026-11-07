#include "../utilities/template.h"

#include "../../content/data-structures/FHQTreap.h"

int main() {
	mt19937 rng(3);
	auto rnd = [&](int lo, int hi) { return lo + (int)(rng() % (unsigned)(hi - lo + 1)); };
	long long checks = 0;

	rep(it, 0, 2000) {
		Treap T;
		multiset<ll> ms;
		int V = rnd(1, 30);
		rep(step, 0, 200) {
			int op = rnd(0, 5);
			ll v = rnd(-V, V);
			if (op <= 1) T.insert(v), ms.insert(v);
			else if (op == 2) {
				T.erase(v);
				auto f = ms.find(v);
				if (f != ms.end()) ms.erase(f);
			} else if (op == 3) {
				assert(T.rank(v) == (int)distance(ms.begin(), ms.lower_bound(v)));
			} else if (op == 4 && !ms.empty()) {
				int k = rnd(0, sz(ms) - 1);
				assert(T.kth(k) == *next(ms.begin(), k));
			} else if (!ms.empty()) {
				auto lb = ms.lower_bound(v);
				if (lb != ms.begin()) assert(T.kth(T.rank(v) - 1) == *prev(lb));
				auto ub = ms.upper_bound(v);
				if (ub != ms.end()) assert(T.kth(T.rank(v + 1)) == *ub);
			}
			assert(T.t[T.rt].s == sz(ms));
			checks++;
		}
		vector<ll> o;
		T.walk(T.rt, o);
		assert(o == vector<ll>(all(ms)));
	}

	rep(it, 0, 2000) {
		Treap T;
		vector<ll> a;
		rep(step, 0, 150) {
			int op = rnd(0, 3);
			if (op == 0 || a.empty()) {
				ll v = rnd(-1000, 1000);
				T.rt = T.merge(T.rt, T.nn(v));
				a.push_back(v);
			} else {
				int l = rnd(0, sz(a)), r = rnd(0, sz(a));
				if (l > r) swap(l, r);
				int x, y, z;
				T.split(T.rt, l, x, y);
				T.split(y, r - l, y, z);
				assert(T.t[y].s == r - l);
				if (op == 1) {
					T.t[y].rev ^= 1;
					reverse(a.begin() + l, a.begin() + r);
				} else {
					assert(T.t[y].sum == accumulate(a.begin() + l, a.begin() + r, 0LL));
				}
				T.rt = T.merge(T.merge(x, y), z);
			}
			checks++;
		}
		vector<ll> o;
		T.walk(T.rt, o);
		assert(o == a);
	}

	{
		Treap T;
		int n = 500000;
		rep(i, 0, n) T.insert(rnd(0, 1000000000));
		int depth = 0;
		function<int(int)> dep = [&](int x) { return x ? 1 + max(dep(T.t[x].l), dep(T.t[x].r)) : 0; };
		depth = dep(T.rt);
		assert(depth < 100);
		cout << "depth with " << n << " nodes: " << depth << endl;
	}
	cout << "Tests passed! (" << checks << " checks)" << endl;
}
