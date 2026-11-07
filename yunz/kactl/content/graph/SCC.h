/**
 * Description: Tarjan 强连通分量. 分量编号是逆拓扑序: 缩点后的边总是
 * 从编号大的指向编号小的. 递归深度可达 $n$, 要开大栈.
 * 对象必须是全局变量.
 * Usage: S.init(n); // 多组数据每组调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v;
 *   S.g[u].push_back(v); // 有向边 u 到 v
 * }
 * for(int i=1;i<=n;i++) if(!S.dfn[i]) S.tarjan(i);
 * int id=S.scc[u]; // u 所在分量, 1..S.cnt
 * int sz=S.sz[id]; // 分量大小
 * S.shrink(n); // 缩点 DAG S.h[1..S.cnt], 可能有重边
 * for(int i=S.cnt;i>=1;i--) // 按拓扑序遍历分量
 *   for(int j:S.h[i]) ...; // 分量 i 到分量 j 的边
 * SCC S2; // 第二个对象 (全局)
 * Time: O(n+m)
 */
#pragma once

struct SCC{
	static const int N=2e5+5;
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
}S;
