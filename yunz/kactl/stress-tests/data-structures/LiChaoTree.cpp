#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/data-structures/LiChaoTree.h"

// Insert segments on [l, r), query max at a point, against brute force.
int main() {
	rep(it,0,20000) {
		int M = randIncl(1, 12);
		LiChao lc(M);
		vector<ll> best(M, LLONG_MIN);
		rep(op,0,20) {
			if (randBool()) {
				int l = randIncl(M), r = randIncl(M); // empty segments allowed
				if (l > r) swap(l, r);
				ll m = randIncl(-10, 10), b = randIncl(-100, 100);
				lc.insert(l, r, {m, b});
				rep(x,l,r) best[x] = max(best[x], m * x + b);
			} else {
				int x = randRange(M);
				assert(lc.query(x) == best[x]);
			}
		}
	}
	// large slopes and intercepts need 64-bit values
	LiChao lc(1000);
	lc.insert(0, 1000, {1000000000, -1000000000000LL});
	assert(lc.query(999) == 999LL * 1000000000 - 1000000000000LL);
	cout<<"Tests passed!"<<endl;
}
