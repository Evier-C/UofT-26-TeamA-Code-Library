#include "../utilities/template.h"
#include "../utilities/utils.h"
#include "../utilities/random.h"

#include "../../content/graph/WeightedMatching.h"
#include "../../content/graph/MinCostMaxFlow.h"

void test(int N, int mxCost, int iters) {
	for (int it = 0; it < iters; it++) {
		int n = randRange(0, N), m = randRange(0, N);
		if (n > m)
			swap(n, m);

		MCMF<ll, ll> mcmf(n + m + 2);
		int s = 0;
		int t = 1;
		for (int i = 0; i < n; i++)
			mcmf.ae(s, i + 2, 1, 0);
		for (int i = 0; i < m; i++)
			mcmf.ae(2 + n + i, t, 1, 0);

		vector<vector<ll>> cost(n, vector<ll>(m));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cost[i][j] = randRange(-mxCost, mxCost);
				mcmf.ae(i + 2, 2 + n + j, 1, cost[i][j]);
			}
		}
		auto maxflow = mcmf.calc(s, t);
		auto matching = hungarian(cost);
		assert(maxflow.first == n);
		assert(maxflow.second == matching.first);
		ll matchSum = 0;
		set<int> used;
		for (int i = 0; i < n; i++) {
			matchSum += cost[i][matching.second[i]];
			assert(used.count(matching.second[i]) == 0);
			used.insert(matching.second[i]);
		}
		assert(matchSum == matching.first);
	}
}
signed main() {
	test(25, 5, 1000);
	test(100, 1000, 100);
	test(100, 1, 50);
	test(5, 5, 10000);
	cout << "Tests passed!" << endl;
}
