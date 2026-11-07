/**
 * Author: Benjamin Qi, 12tqian
 * Date: 2026-01-30
 * Source: https://12tqian.github.io/cp-library/library/graphs/flows/min-cost-max-flow.hpp.html
 *
 * Description: 最小费用最大流, 要求无负环. 可以构造负边权使第一次
 * Dijkstra 很慢, 但实践中没出过问题. 之后每轮 (加势能后) 边权都 $\ge 0$.
 * 想得到原边上的流量, 在 \texttt{ae} 时记下边的编号.
 * Usage: MCMF<ll, ll> mf(n); mf.ae(u, v, cap, cost);
 * auto [fl, co] = mf.calc(s, t); // 最大流 与 最小费用
 * mf.edges[2 * i].flow // 第 i 次 ae 的边上的流量
 * Time: 不计第一次 Dijkstra, 若容量为整数且 $F$ 为最大流,
 * 则为 $O(FM\log M)$.
 */
#pragma once
template <class F, class C> // F 为流量类型 ; C 为费用类型
struct MCMF {
    struct Edge { int to; F flow, cap; C cost; };

    int n;
    vector<C> p, dist;
    vector<int> pre;
    vector<Edge> edges;
    vector<vector<int>> adj;

    const C INF = numeric_limits<C>::max() / 4;

    MCMF(int n) : n(n), p(n), dist(n), pre(n), adj(n) {}

    void ae(int u, int v, F cap, C cost) {
        assert(cap >= 0);
        adj[u].push_back(sz(edges));
        edges.push_back({v, 0, cap, cost});
        adj[v].push_back(sz(edges));
        edges.push_back({u, 0, 0, -cost});
    }

    bool path(int s, int t) {
        for (int i = 0; i < n; i++)
            dist[i] = INF;
        using T = pair<C, int>;
        priority_queue<T, vector<T>, greater<>> todo;
        todo.push({dist[s] = 0, s});
        while (!todo.empty()) {
            T x = todo.top();
            todo.pop();
            if (x.first > dist[x.second])
                continue;
            for (auto& eid : adj[x.second]) {
                const Edge& e = edges[eid];
                if (e.flow < e.cap && dist[e.to]
					> x.first + e.cost + p[x.second] - p[e.to]) {
                    dist[e.to] = x.first + e.cost + p[x.second] - p[e.to];
                    pre[e.to] = eid;
                    todo.push({dist[e.to], e.to});
                }
            }
        }
        return dist[t] != INF;
    }

    pair<F, C> calc(int s, int t) {
        assert(s != t);
        for (int unused = 0; unused < n; unused++)
            for (int eid = 0; eid < (int)edges.size(); eid++) {
                const Edge& e = edges[eid];
                if (e.cap)
                    p[e.to] = min(p[e.to], p[edges[eid ^ 1].to] + e.cost);
            }
        F totflow = 0;
        C totcost = 0;
        while (path(s, t)) {
            for (int i = 0; i < n; i++)
                p[i] = min(p[i] + dist[i], INF);
            F df = numeric_limits<F>::max() / 4;
            for (int x = t; x != s; x = edges[pre[x] ^ 1].to) {
                const Edge& e = edges[pre[x]];
                df = min(df, e.cap - e.flow);
            }
            totflow += df;
            totcost += (p[t] - p[s]) * df;
            for (int x = t; x != s; x = edges[pre[x] ^ 1].to)
                edges[pre[x]].flow += df, edges[pre[x] ^ 1].flow -= df;
        }
        return {totflow, totcost};
    }
};