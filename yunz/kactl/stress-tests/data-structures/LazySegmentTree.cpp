#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/data-structures/LazySegmentTree.h"

// Default ops: range add, range max, point set/get. Ranges are [l, r).
void test(int N, int iters, int ops) {
	rep(it,0,iters) {
		lztree tr(N);
		vector<ll> v(N);
		rep(i,0,N) tr.set(i, v[i] = randIncl(-5, 5));
		rep(op,0,ops) {
			int i = randIncl(N), j = randIncl(N); // empty ranges allowed
			if (i > j) swap(i, j);
			int r = randRange(100);
			if (r < 30) {
				ll ma = idT;
				rep(k,i,j) ma = max(ma, v[k]);
				assert(ma == tr.query(i, j));
			} else if (r < 70) {
				ll x = randIncl(-5, 5);
				tr.update(i, j, x);
				rep(k,i,j) v[k] += x;
			} else if (i < N) {
				if (r < 85) {
					ll x = randIncl(-5, 5);
					tr.set(i, x);
					v[i] = x;
				} else assert(tr.get(i) == v[i]);
			}
		}
	}
}

int main() {
	rep(N,1,70) test(N, 100, 100);
	test(1000, 10, 2000);
	test((1 << 17) + 3, 1, 1000);
	cout<<"Tests passed!"<<endl;
}
