#include "../utilities/template.h"
#include "../utilities/random.h"

#define pb push_back
#include "../../content/graph/FunctionalGraph.h"

int main() {
	rep(it,0,50000) {
		int n = randIncl(8);
		vi a(n);
		rep(i,0,n) a[i] = randRange(n);
		auto [root_of, cycles, childs] = func_graph(a);
		vector<bool> onCycle(n);
		rep(v,0,n) {
			int u = a[v];
			rep(k,0,n) {
				if (u == v) { onCycle[v] = 1; break; }
				u = a[u];
			}
		}
		// every cycle is listed once, in edge order, with root_of = (cycle, pos)
		vector<bool> seen(n);
		rep(c,0,sz(cycles)) {
			int L = sz(cycles[c]);
			rep(p,0,L) {
				int u = cycles[c][p];
				assert(onCycle[u] && !seen[u]);
				seen[u] = 1;
				assert(a[u] == cycles[c][(p + 1) % L]);
				assert(root_of[u] == pii(c, p));
			}
		}
		rep(v,0,n) assert(seen[v] == onCycle[v]);
		// root = first cycle node reached from v
		rep(v,0,n) {
			int u = v;
			while (!onCycle[u]) u = a[u];
			auto [ci, cp] = root_of[v];
			assert(cycles[ci][cp] == u);
		}
		// childs = reversed edges not on cycles
		vector<multiset<int>> expected(n);
		rep(v,0,n) if (!onCycle[v]) expected[a[v]].insert(v);
		rep(v,0,n) assert(multiset<int>(all(childs[v])) == expected[v]);
	}
	cout<<"Tests passed!"<<endl;
}
