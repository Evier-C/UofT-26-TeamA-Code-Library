/**
 * Description: Tarjan 求有向图强连通分量 (点 $1..n$). scc[u] 为 $u$
 * 所在分量编号 ($1..cnt$), sz[i] 为分量 $i$ 的点数. Tarjan 得到的编号是
 * 逆拓扑序: 缩点后的边总是从编号大的分量指向编号小的分量,
 * 所以按 $cnt, cnt-1, \dots, 1$ 的顺序就是 DAG 的拓扑序.
 * shrink 建缩点后的 DAG h[1..cnt] (可能有重边, 需要时去重).
 * Usage: init(n); g[u].push_back(v);
 * for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
 * shrink(n); // 可选
 * for(int i=cnt;i>=1;i--) ... // 按拓扑序 DP
 * Time: O(n+m)
 */
#pragma once

const int N=2e5+5;
vector<int>g[N],h[N]; // h 为缩点后的 DAG
int dfn[N],low[N],stk[N],tp,tim;
int scc[N],sz[N],cnt;bool ins[N];
void tarjan(int u){
	dfn[u]=low[u]=++tim,stk[++tp]=u,ins[u]=1;
	for(int v:g[u]){
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(ins[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		cnt++;int v;
		do v=stk[tp--],ins[v]=0,scc[v]=cnt,sz[cnt]++;
		while(v!=u);
	}
}
void shrink(int n){
	for(int u=1;u<=n;u++)for(int v:g[u])
		if(scc[u]!=scc[v])h[scc[u]].push_back(scc[v]);
}
void init(int n){
	for(int i=1;i<=n;i++)
		g[i].clear(),h[i].clear(),dfn[i]=sz[i]=0;
	tim=tp=cnt=0;
}
