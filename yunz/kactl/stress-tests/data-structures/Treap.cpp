#include "../utilities/template.h"
#include "../utilities/random.h"

#define rall(x) (x).rbegin(), (x).rend()
mt19937 rng(2);
#include "../../content/data-structures/Treap.h"

// Default ops: range reverse (U = bool, xor), range sum (T = int).
void collect(ptr a, vi& out) {
	if (!a) return;
	_push(a);
	collect(a->l, out);
	out.push_back(a->val);
	collect(a->r, out);
}

int main() {
	rep(it,0,3000) {
		_last = 0;
		int n = randIncl(0, 60);
		vi v(n);
		for (int& x : v) x = randIncl(-9, 9);
		ptr root = build(v);
		rep(q,0,60) {
			int l = randIncl(n), r = randIncl(n); // empty ranges allowed
			if (l > r) swap(l, r);
			if (randBool()) {
				root = range_apply(root, l, r, true);
				reverse(v.begin() + l, v.begin() + r);
			} else {
				int s = 0;
				rep(i,l,r) s += v[i];
				assert(range_query(root, l, r) == s);
			}
			if (q % 10 == 0) { // merge/split must preserve the sequence
				int k = randIncl(n);
				auto [a, b] = split(root, k);
				assert(_getsiz(a) == k && _getsiz(b) == n - k);
				root = merge(a, b);
			}
			vi got;
			collect(root, got);
			assert(got == v);
			assert(_getsiz(root) == n);
		}
	}
	cout<<"Tests passed!"<<endl;
}
