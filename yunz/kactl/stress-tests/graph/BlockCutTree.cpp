#include "../utilities/template.h"
#include "../utilities/random.h"

#define pb push_back
#include "../../content/graph/BlockCutTree.h"

// Connected graphs (multi-edges allowed), 0- or 1-indexed.
// Cut vertices: removing v increases the number of components.
// Blocks: two edges are in the same block iff no single vertex removal
// separates them.
int main() {
	rep(it,0,30000) {
		int n = randIncl(1, 8), s = randIncl(1), N = n + s;
		vector<vi> g(N);
		vector<pii> E;
		auto add = [&](int a, int b) {
			g[a + s].push_back(b + s), g[b + s].push_back(a + s), E.push_back({a, b});
		};
		rep(i,1,n) add(i, randRange(i));
		rep(k,0,randIncl(5)) {
			int a = randRange(n), b = randRange(n);
			if (a != b) add(a, b);
		}
		rep(u,0,N) shuffle_vec(g[u]);
		auto [t, isCut, id] = blockCutTree(g, s);

		auto compsWithout = [&](int v) { // component label of each vertex
			vi c(n, -1);
			int k = 0;
			rep(st,0,n) if (st != v && c[st] < 0) {
				c[st] = k;
				vi q = {st};
				while (!q.empty()) {
					int u = q.back(); q.pop_back();
					for (int w : g[u + s]) if (w - s != v && c[w - s] < 0)
						c[w - s] = k, q.push_back(w - s);
				}
				k++;
			}
			return pair(c, k);
		};
		vector<vi> label(n);
		int ncut = 0;
		rep(v,0,n) {
			auto [c, k] = compsWithout(v);
			label[v] = c;
			assert(isCut[v + s] == (k > 1));
			ncut += k > 1;
		}
		int m = sz(E);
		auto edgeLabel = [&](int v, int e) {
			auto [a, b] = E[e];
			return label[v][a != v ? a : b];
		};
		vi cls(m, -1);
		set<vi> blocks;
		rep(e,0,m) if (cls[e] < 0) {
			set<int> vs;
			rep(f,e,m) if (cls[f] < 0) {
				bool same = true;
				rep(v,0,n) if (edgeLabel(v, e) != edgeLabel(v, f)) same = false;
				if (same) cls[f] = e, vs.insert(E[f].first), vs.insert(E[f].second);
			}
			blocks.insert(vi(all(vs)));
		}
		if (n == 1) blocks.insert({0});

		// tree nodes: cut vertices first, then one node per block
		assert(sz(t) == ncut + sz(blocks));
		set<vi> got;
		rep(node,ncut,sz(t)) {
			vi vs;
			rep(v,0,n) if (!isCut[v + s] && id[v + s] == node) vs.push_back(v);
			for (int c : t[node]) rep(v,0,n) if (isCut[v + s] && id[v + s] == c) vs.push_back(v);
			sort(all(vs));
			got.insert(vs);
		}
		assert(got == blocks);
	}
	cout<<"Tests passed!"<<endl;
}
