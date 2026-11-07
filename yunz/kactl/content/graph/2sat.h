/**
 * Description: 2-SAT (变量 $1..n$). 点 $x$ 表示 $x$ 为真, 点 $x+n$ 表示
 * $x$ 为假. 子句 $a \lor b$ 连边 $\lnot a \to b$, $\lnot b \to a$, 再用 Tarjan
 * 求 SCC. 无解当且仅当某个 $x$ 与 $x+n$ 在同一个 SCC. 有解时取
 * scc 编号小的那一边 (Tarjan 编号是逆拓扑序, 编号小的在拓扑序后面).
 * Usage: init(n); // 多组数据重新调用
 * add(x,1,y,0); // 子句: x 为真 或 y 为假
 * add(x,1,x,1); // 强制 x 为真
 * if(!solve()) 无解; else ans[1..n] 为一组解 (1 为真)
 * Time: O(n+m)
 */
#pragma once

const int N=2e5+5; // 变量数, 点数为 2N
int n,dfn[N*2],low[N*2],stk[N*2],tp,tim,scc[N*2],cnt,ans[N];
bool ins[N*2];vector<int>g[N*2];
void tarjan(int u){
	dfn[u]=low[u]=++tim,stk[++tp]=u,ins[u]=1;
	for(int v:g[u]){
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(ins[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		cnt++;int v;
		do v=stk[tp--],ins[v]=0,scc[v]=cnt;while(v!=u);
	}
}
// 子句: (x 取值 a) 或 (y 取值 b), a,b 为 0/1
void add(int x,int a,int y,int b){
	g[a?x+n:x].push_back(b?y:y+n); // x 不取 a 则 y 取 b
	g[b?y+n:y].push_back(a?x:x+n); // y 不取 b 则 x 取 a
}
bool solve(){
	for(int i=1;i<=2*n;i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++){
		if(scc[i]==scc[i+n])return 0;
		ans[i]=scc[i]<scc[i+n];
	}
	return 1;
}
void init(int _n){
	n=_n,tim=tp=cnt=0;
	for(int i=1;i<=2*n;i++)g[i].clear(),dfn[i]=0;
}
