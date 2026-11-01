#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/numerical/MaxPlusConvolution.h"

// c_k = max(a_k, max_{i+j+1=k} a_i + b_j): a zero is implicitly prepended to b.
int main() {
	rep(it,0,200000) {
		int na = randIncl(39), nb = randIncl(39);
		vll a(na), b(nb), d(nb);
		for (ll& x : a) x = randIncl(-20, 20);
		for (ll& x : d) x = randIncl(-10, 10);
		sort(d.rbegin(), d.rend()); // nonincreasing differences => concave
		if (randRange(3) == 0) fill(all(d), randIncl(-3, 3)); // linear b
		if (randRange(4) == 0) for (ll& x : a) x = randIncl(-2, 2); // many ties
		ll cur = randIncl(-20, 20);
		rep(i,0,nb) b[i] = cur, cur += d[i];
		vll expected(na);
		rep(k,0,na) {
			expected[k] = a[k];
			rep(i,0,k) if (k - i - 1 < nb) expected[k] = max(expected[k], a[i] + b[k - i - 1]);
		}
		assert(maxPlusConv(a, b) == expected);
	}
	cout<<"Tests passed!"<<endl;
}
