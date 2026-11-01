#include "../utilities/template.h"
#include "../utilities/genTree.h"

#include "../../content/graph/HLD.h"

namespace old {
#include "oldHLD.h"
}
struct bruteforce { // values in nodes
	vector<vector<int>> tree;
	vector<int> vals;
	vector<int> pars;
	int unit = -1e9;
	int f(int a, int b) { return max(a, b); }
	void root(int cur, int p = -1) {
		pars[cur] = p;
		for (auto i: tree[cur]) {
			if (i != p) root(i, cur);
		}
	}
	bruteforce(vector<vector<int>> _tree): tree(_tree), vals(sz(tree)), pars(sz(tree)) {
		root(0);
	}
	bool dfsModify(int cur, int target, int val, int p=-1) {
		if (cur == target) {
			vals[cur] += val;
			return true;
		}
		bool alongPath = false;
		for (auto i: tree[cur]) {
			if (i == p) continue;
			alongPath |= dfsModify(i, target, val, cur);
		}
		if (alongPath) vals[cur] += val;
		return alongPath;
	}
	void modifyPath(int a, int b, int val) {
		dfsModify(a, b, val);
	}

	int dfsQuery(int cur, int target, int p = -1) {
		if (cur == target) {
			return vals[cur];
		}
		int res = unit;
		for (auto i: tree[cur]) {
			if (i == p) continue;
			res = f(res, dfsQuery(i, target, cur));
		}
		if (res != unit) {
			return f(res, vals[cur]);
		}
		return res;
	}
	int queryPath(int a, int b) {
		return dfsQuery(a, b);
	}
	int dfsSubtree(int cur, int p) {
		int res = vals[cur];
		for (auto i: tree[cur]) {
			if (i != p)
				res = f(res, dfsSubtree(i, cur));
		}
		return res;
	}
	int querySubtree(int a) {
		return dfsSubtree(a, pars[a]);
	}
};

void testAgainstOld(int n, int iters, int queries) {
	for (int trees = 0; trees < iters; trees++) {
		auto graph = genRandomTree(n);
		vector<vector<int>> tree1(n);
		vector<vector<pair<int, int>>> tree2(n);
		for (auto i : graph) {
			tree1[i.first].push_back(i.second);
			tree1[i.second].push_back(i.first);
		}
		for (int i = 0; i < sz(tree1); i++) {
			for (auto j : tree1[i]) {
				tree2[i].push_back({j, 0});
			}
		}
		HLD<false> hld(tree1, vector<T>(n, 0), 0);
		old::HLD hld2(tree2);
		for (int itr = 0; itr < queries; itr++) {
			if (rand() % 2) {
				int node = rand() % n;
				int val = rand() % 10;
				hld2.update(node, val);
				hld.modifyPath(node, node, val - hld.queryPath(node, node));
			} else {
				int a = rand() % n;
				int b = rand() % n;
				assert(hld.queryPath(a, b) == hld2.query2(a, b).first);
			}
		}
	}
}
void testAgainstBrute(int n, int iters, int queries) {
	for (int trees = 0; trees < iters; trees++) {
		auto graph = genRandomTree(n);
		vector<vector<int>> tree1(n);
		for (auto i : graph) {
			tree1[i.first].push_back(i.second);
			tree1[i.second].push_back(i.first);
		}
		HLD<false> hld(tree1, vector<T>(n, 0), 0);
		bruteforce hld2(tree1);
		for (int itr = 0; itr < queries; itr++) {
			int rng = rand() % 3;
			if (rng == 0) {
				int a = rand() % n;
				int b = rand() % n;
				int val = rand() % 10;
				hld.modifyPath(a, b, val);
				hld2.modifyPath(a, b, val);
			} else if (rng == 1){
				int a = rand() % n;
				int b = rand() % n;
				hld.queryPath(a, b);
				hld2.queryPath(a, b);
				assert(hld.queryPath(a, b) == hld2.queryPath(a, b));
			} else if (rng == 2) {
				int a = rand() % n;
				assert(hld.querySubtree(a) == hld2.querySubtree(a));
			}
		}
	}

}
// Arbitrary root, random initial values, values on nodes or on edges
// (edge (u, par[u]) stored at u). Default ops: path/subtree add, max.
template<bool E> void testRooted(int n, int iters, int queries) {
	const ll NEG = idT;
	rep(it,0,iters) {
		auto graph = genRandomTree(n);
		vector<vi> adj(n);
		for (auto e : graph) adj[e.first].push_back(e.second), adj[e.second].push_back(e.first);
		int root = rand() % n;
		vi par(n, -1), dep(n), st = {root};
		vector<bool> vis(n);
		vis[root] = 1;
		while (!st.empty()) {
			int x = st.back(); st.pop_back();
			for (int y : adj[x]) if (!vis[y])
				vis[y] = 1, par[y] = x, dep[y] = dep[x] + 1, st.push_back(y);
		}
		vector<ll> a(n);
		for (auto& x : a) x = rand() % 19 - 9;
		if (E) a[root] = NEG;
		HLD<E> h(adj, vector<T>(all(a)), root);
		auto path = [&](int u, int v) {
			vi p;
			while (u != v) { if (dep[u] < dep[v]) swap(u, v); p.push_back(u); u = par[u]; }
			if (!E) p.push_back(u);
			return p;
		};
		auto inSub = [&](int v, int x) { for (; x != -1; x = par[x]) if (x == v) return true; return false; };
		auto same = [&](ll x, ll y) { return x == y || (x <= NEG / 2 && y <= NEG / 2); };
		rep(q,0,queries) {
			int u = rand() % n, v = rand() % n, k = rand() % 4;
			if (k == 0) {
				ll x = rand() % 11 - 5;
				h.modifyPath(u, v, x);
				for (int y : path(u, v)) a[y] += x;
			} else if (k == 1) {
				ll e = NEG;
				for (int y : path(u, v)) e = max(e, a[y]);
				assert(same(h.queryPath(u, v), e));
			} else if (k == 2) {
				ll e = NEG;
				rep(y,0,n) if (inSub(u, y) && !(E && y == u)) e = max(e, a[y]);
				assert(same(h.querySubtree(u), e));
			} else if (!(E && u == root)) assert(h.get(u) == a[u]);
		}
	}
}

int main() {
	srand(2);
	testAgainstBrute(5, 1000, 10000);
	testAgainstBrute(1000, 100, 100);
	testAgainstOld(5, 1000, 100);
	testAgainstOld(10000, 100, 1000);
	rep(n,2,30) testRooted<false>(n, 100, 50), testRooted<true>(n, 100, 50); // genRandomTree needs n >= 2
	testRooted<false>(300, 20, 300);
	testRooted<true>(300, 20, 300);
	cout<<"Tests passed!"<<endl;
	return 0;
}
