#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/graph/DynamicConnectivity.h"

// Random edge toggles over times 0..t on vertices 1..n (1-indexed DSU of
// size n+1); ans[time] = number of components at queried times.
int main() {
	rep(it,0,20000) {
		int n = randIncl(1, 6), t = randIncl(14);
		DynConn dc(t);
		map<pii, int> start;
		vector<set<pii>> alive(t + 1);
		set<pii> cur;
		vi isQuery(t + 1);
		rep(i,0,t+1) {
			int op = randRange(3);
			if (op == 0) {
				int a = randIncl(1, n), b = randIncl(1, n);
				if (a > b) swap(a, b);
				pii e = {a, b};
				if (cur.count(e)) dc.add_edge(start[e], i - 1, e), cur.erase(e), start.erase(e);
				else cur.insert(e), start[e] = i;
			} else if (op == 1) {
				dc.add_query(i);
				isQuery[i] = 1;
			}
			alive[i] = cur;
		}
		for (auto [e, s0] : start) dc.add_edge(s0, t, e);
		RollbackUF uf(n + 1);
		dc.solve(uf);
		rep(i,0,t+1) {
			if (!isQuery[i]) {
				assert(dc.ans[i] == -1);
				continue;
			}
			vi p(n + 1);
			iota(all(p), 0);
			function<int(int)> find = [&](int x) { return p[x] == x ? x : p[x] = find(p[x]); };
			int comps = n;
			for (auto [a, b] : alive[i]) if (find(a) != find(b)) p[find(a)] = find(b), comps--;
			assert(dc.ans[i] == comps);
		}
	}
	cout<<"Tests passed!"<<endl;
}
