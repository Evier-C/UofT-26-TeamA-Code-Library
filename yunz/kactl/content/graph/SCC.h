/**
 * Description: Tarjan 求有向图强连通分量 (SCC), 点 $1..n$.
 * 输入: 有向边存在 g[u] 中 (u 到 v 则 g[u].push\_back(v)).
 * 对每个未访问的点 (dfn 为 0) 调用 tarjan(i).
 * 结果: scc[u] 为点 $u$ 所在分量编号 ($1..cnt$), sz[i] 为分量 $i$ 的
 * 点数, cnt 为分量个数. Tarjan 的编号是逆拓扑序: 缩点后的边总是
 * 从编号大的分量指向编号小的分量, 所以 $cnt, cnt-1, \dots, 1$ 就是
 * DAG 的拓扑序, 可以直接按这个顺序 DP.
 * shrink(n) 建缩点后的 DAG, 存在 h[1..cnt] 中 (可能有重边, 需要时去重).
 * 注意: 递归深度可达 $n$, 链状图要开大栈. N 为点数上限.
 * Usage: init(n); // 多组数据每组调用, 清空 g, h, dfn 等
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v;
 *   g[u].push_back(v);
 * }
 * for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
 * shrink(n); // 需要 DAG 时调用
 * for(int i=cnt;i>=1;i--) // 按拓扑序遍历分量
 *   for(int j:h[i]) ...; // 分量 i 到分量 j 的边
 * Time: O(n+m)
 */
#pragma once

const int N=2e5+5;
vector<int>g[N],h[N]; // g 原图, h 缩点后的 DAG
int dfn[N],low[N],stk[N],tp,tim;
int scc[N],sz[N],cnt;
bool ins[N]; // 是否在栈中
void tarjan(int u){
	dfn[u]=low[u]=++tim;
	stk[++tp]=u;
	ins[u]=1;
	for(int v:g[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(ins[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){ // u 是分量的根, 弹栈
		cnt++;
		int v;
		do{
			v=stk[tp--];
			ins[v]=0;
			scc[v]=cnt;
			sz[cnt]++;
		}while(v!=u);
	}
}
void shrink(int n){
	for(int u=1;u<=n;u++){
		for(int v:g[u]){
			if(scc[u]!=scc[v])h[scc[u]].push_back(scc[v]);
		}
	}
}
void init(int n){
	for(int i=1;i<=n;i++){
		g[i].clear();
		h[i].clear();
		dfn[i]=sz[i]=0;
	}
	tim=tp=cnt=0;
}
