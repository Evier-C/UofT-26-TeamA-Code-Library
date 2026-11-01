#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/number-theory/ModularArithmetic.h"

template<int M> void test() {
	typedef mint<M> mi;
	auto norm = [](ll x) { return ((x % M) + M) % M; };
	rep(it,0,200000) {
		ll a = randIncl((int64_t)-4e18, (int64_t)4e18);
		ll b = randIncl((int64_t)-4e18, (int64_t)4e18);
		ll ra = norm(a), rb = norm(b);
		mi x = a, y = b;
		assert((int)x == ra);
		assert((int)(x + y) == (ra + rb) % M);
		assert((int)(x - y) == norm(ra - rb));
		assert((int)(x * y) == (ll)((__int128)ra * rb % M));
		if (ra) assert((int)(inv(x) * x) == 1);
		ll e = randIncl((int64_t)0, (int64_t)1e18), r = 1, bb = ra;
		for (ll ee = e; ee; ee >>= 1, bb = (ll)((__int128)bb * bb % M))
			if (ee & 1) r = (ll)((__int128)r * bb % M);
		assert((int)pow(x, e) == r);
	}
}

int main() {
	typedef mint<17> mi;
	rep(a,0,17) rep(b,1,17) {
		mi ma(a), mb(b);
		assert((int)(ma * inv(mb) * mb) == a);
	}
	mi two = 2;
	ll cur = 1;
	rep(i,0,40) {
		assert((int)pow(two, i) == cur);
		cur = cur * 2 % 17;
	}
	test<17>();
	test<998244353>();
	test<1000000007>();
	cout<<"Tests passed!"<<endl;
}
