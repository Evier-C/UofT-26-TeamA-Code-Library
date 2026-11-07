/**
 * Description: Kahn 拓扑排序 (点 $1..n$). 返回是否为 DAG,
 * 拓扑序在 ord[1..cnt]. 有环时 cnt $< n$, 环上及环能到达的点不会出现.
 * 求字典序最小的拓扑序: 把 queue 换成小根堆 priority\_queue.
 * Usage: for(i=1..n) g[i].clear(); g[u].push_back(v); // 边 u 到 v
 * if(!topo(n)) 有环; 否则 ord[1..n] 为拓扑序
 * Time: O(n+m)
 */
#pragma once

const int N=2e5+5;
vector<int>g[N];
int deg[N],ord[N],cnt;
bool topo(int n){
	for(int i=1;i<=n;i++)deg[i]=0;
	for(int u=1;u<=n;u++)for(int v:g[u])deg[v]++;
	queue<int>q;cnt=0;
	for(int i=1;i<=n;i++)if(!deg[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();ord[++cnt]=u;
		for(int v:g[u])if(--deg[v]==0)q.push(v);
	}
	return cnt==n;
}
