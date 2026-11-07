#include "../utilities/template.h"

#include "../../content/number-theory/ExLucas.h"

int main() {
	mt19937 rng(17);
	long long checks = 0;
	int N = 200;
	auto pascal = [&](ll P) {
		vector<vector<ll>> C(N + 1, vector<ll>(N + 1, 0));
		rep(n, 0, N + 1) {
			C[n][0] = 1 % P;
			rep(m, 1, n + 1) C[n][m] = (C[n - 1][m - 1] + C[n - 1][m]) % P;
		}
		return C;
	};
	// small moduli: every (n, m)
	vector<ll> small = {1, 2, 4, 8, 3, 9, 27, 6, 12, 36, 100, 360, 1000, 30030, 1024, 729};
	for (ll P : small) {
		auto C = pascal(P);
		rep(n, 0, N + 1) rep(m, -2, n + 3) {
			ll want = (m < 0 || m > n) ? 0 : C[n][m];
			assert(exlucas(n, m, P) == want);
			checks++;
		}
	}
	// larger moduli: random (n, m)
	vector<ll> big = {99991, 65536, 59049, 362880, 1000000, 999983};
	rep(i, 0, 14) big.push_back(1 + (ll)(rng() % 1000000));
	for (ll P : big) {
		auto C = pascal(P);
		rep(k, 0, 40) {
			int n = (int)(rng() % (N + 1)), m = (int)(rng() % (n + 1));
			assert(exlucas(n, m, P) == C[n][m]);
			checks++;
		}
	}
	cout << "Tests passed! (" << checks << " checks)" << endl;
}
