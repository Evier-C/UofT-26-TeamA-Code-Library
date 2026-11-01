#include "../utilities/template.h"
#include "../utilities/genTree.h"

#define pb push_back
#define F first
#define S second
#include "../../content/graph/AllRoots.h"

// Default ART: res[v] = max over u of (base + dist(u, v)).
// base is set to a nonzero value so that it must be counted for every node
// (including n = 1).
int main() {
	srand(3);
	rep(it,0,3000) {
		int n = rand() % 30 + 1;
		vector<pii> el;
		if (n >= 2) for (auto e : genRandomTree(n)) el.push_back(e);
		vector<vi> g(n);
		for (auto [a, b] : el) g[a].push_back(b), g[b].push_back(a);
		int k = rand() % 5;
		base = {k};
		auto res = AllRoots<ART>::calc(el);
		rep(s,0,n) {
			vi d(n, -1);
			d[s] = 0;
			queue<int> q;
			q.push(s);
			int ecc = 0;
			while (!q.empty()) {
				int x = q.front(); q.pop();
				ecc = max(ecc, d[x]);
				for (int y : g[x]) if (d[y] < 0) d[y] = d[x] + 1, q.push(y);
			}
			assert(res[s].ans == k + ecc);
		}
	}
	cout<<"Tests passed!"<<endl;
}
