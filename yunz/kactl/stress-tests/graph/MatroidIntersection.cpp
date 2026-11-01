#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/graph/MatroidIntersection.h"

// Partition matroid with per-color capacities.
struct CapMat {
	vi cap, cnt, clr;
	CapMat(vi cap, vi clr) : cap(cap), cnt(sz(cap)), clr(clr) {}
	bool check(int x) { return cnt[clr[x]] < cap[clr[x]]; }
	void add(int x) { cnt[clr[x]]++; }
	void clear() { fill(all(cnt), 0); }
};

int main() {
	rep(it,0,6000) {
		int n = randIncl(10), V = randIncl(1, 5), C = randIncl(1, 5);
		vector<array<int, 2>> e(n);
		vi clr(n), clr2(n), cap(C);
		rep(i,0,n) e[i] = {randRange(V), randRange(V)}, clr[i] = randRange(C), clr2[i] = randRange(C);
		rep(i,0,C) cap[i] = randIncl(2);
		int type = randRange(3);
		auto forest = [&](int mask) {
			UF uf(V);
			rep(i,0,n) if (mask >> i & 1) if (!uf.join(e[i][0], e[i][1])) return false;
			return true;
		};
		auto colorful = [&](int mask) {
			vi c(C);
			rep(i,0,n) if (mask >> i & 1) if (++c[clr[i]] > 1) return false;
			return true;
		};
		auto capped = [&](int mask) {
			vi c(C);
			rep(i,0,n) if (mask >> i & 1) if (++c[clr2[i]] > cap[clr2[i]]) return false;
			return true;
		};
		auto indep1 = [&](int mask) { return type == 2 ? colorful(mask) : forest(mask); };
		auto indep2 = [&](int mask) { return type == 0 ? colorful(mask) : capped(mask); };
		int best = 0;
		rep(mask,0,1<<n) if (indep1(mask) && indep2(mask)) best = max(best, __builtin_popcount(mask));
		vi res;
		if (type == 0) res = MatroidIsect<GraphMat, ColorMat>(GraphMat(V, e), ColorMat(C, clr), n).solve();
		else if (type == 1) res = MatroidIsect<GraphMat, CapMat>(GraphMat(V, e), CapMat(cap, clr2), n).solve();
		else res = MatroidIsect<ColorMat, CapMat>(ColorMat(C, clr), CapMat(cap, clr2), n).solve();
		int mask = 0;
		for (int x : res) mask |= 1 << x;
		assert(sz(res) == best && indep1(mask) && indep2(mask));
	}
	cout<<"Tests passed!"<<endl;
}
