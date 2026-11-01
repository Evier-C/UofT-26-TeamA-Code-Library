#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/number-theory/Fractions.h"

typedef pair<ll, ll> R;
R normalize(ll p, ll q) {
	if (q < 0) p = -p, q = -q;
	ll g = gcd(p, q);
	return {p / g, q / g};
}
void check(frac f, R e) { assert(f.p == e.first && f.q == e.second); }

int main() {
	rep(it,0,200000) {
		int p1 = randIncl(-20, 20), q1 = randIncl(-20, 20);
		int p2 = randIncl(-20, 20), q2 = randIncl(-20, 20);
		if (!q1 || !q2) continue;
		frac a(p1, q1), b(p2, q2);
		R A = normalize(p1, q1), B = normalize(p2, q2);
		check(a, A);
		check(a + b, normalize(A.first * B.second + A.second * B.first, A.second * B.second));
		check(a - b, normalize(A.first * B.second - A.second * B.first, A.second * B.second));
		check(a * b, normalize(A.first * B.first, A.second * B.second));
		if (B.first) check(a / b, normalize(A.first * B.second, A.second * B.first));
		assert((a < b) == (A.first * B.second < B.first * A.second));
		assert((a == b) == (A == B));
	}
	check(frac(0, -5), {0, 1});
	cout<<"Tests passed!"<<endl;
}
