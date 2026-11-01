#include "../utilities/template.h"

#define pb push_back
#include "../../content/number-theory/SqrtIntervals.h"

// Intervals must cover 1..n in order, be constant on the value, and be
// maximal (adjacent intervals have different values). The value is monotone
// in i, so checking both endpoints suffices for large n.
template<class V> void check(int n, const vector<pii>& segs, V val) {
	int at = 1;
	rep(k,0,sz(segs)) {
		auto [l, r] = segs[k];
		assert(l == at && l <= r);
		assert(val(l) == val(r));
		if (n <= 3000) rep(i,l,r+1) assert(val(i) == val(l));
		if (k) assert(val(l) != val(segs[k - 1].first));
		at = r + 1;
	}
	assert(at == n + 1);
}

int main() {
	rep(n,1,3001) {
		check(n, fdivSplit(n), [&](int i) { return n / i; });
		check(n, cdivSplit(n), [&](int i) { return (n + i - 1) / i; });
	}
	for (int n : {1000000000, 999999937, 123456789}) {
		check(n, fdivSplit(n), [&](int i) { return n / i; });
		check(n, cdivSplit(n), [&](int i) { return (n + i - 1) / i; });
	}
	cout<<"Tests passed!"<<endl;
}
