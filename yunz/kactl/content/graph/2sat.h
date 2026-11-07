/**
 * Description: 2-SAT: $n$ 个布尔变量 (编号 $1..n$), 若干形如
 * ($x$ 取 $a$) 或 ($y$ 取 $b$) 的子句, 求一组满足所有子句的赋值.
 * 建图: 点 $x$ 表示 $x$ 为真, 点 $x+n$ 表示 $x$ 为假. 子句 $p \lor q$
 * 连边 $\lnot p \to q$ 和 $\lnot q \to p$, 再用 Tarjan 求 SCC.
 * add(x,a,y,b): 加子句 ($x$ 取 $a$) 或 ($y$ 取 $b$), $a, b \in \{0, 1\}$.
 * 强制 $x$ 取 $a$: add(x,a,x,a). 两者不能同时为真: add(x,0,y,0).
 * solve(): 无解返回 0 (某个 $x$ 与 $x+n$ 在同一 SCC); 有解返回 1,
 * ans[x] 为 1 表示 $x$ 为真. 取法: 选 scc 编号小的那一边 (Tarjan 编号
 * 是逆拓扑序, 编号小的在拓扑序后面).
 * 注意: N 为变量数上限, 数组开 2N; 递归深度可达 $2n$, 要开大栈.
 * Usage: init(n); // 多组数据每组调用
 * for(int i=1;i<=m;i++){
 *   cin>>x>>a>>y>>b; // x 取 a 或 y 取 b
 *   add(x,a,y,b);
 * }
 * bool ok=solve(); // 0 表示无解
 * if(ok) for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
 * Time: O(n+m)
 */
#pragma once

const int N=2e5+5; // 变量数, 点数为 2N
int n,dfn[N*2],low[N*2],stk[N*2],tp,tim;
int scc[N*2],cnt,ans[N];
bool ins[N*2];
vector<int>g[N*2];
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
	if(low[u]==dfn[u]){
		cnt++;
		int v;
		do{
			v=stk[tp--];
			ins[v]=0;
			scc[v]=cnt;
		}while(v!=u);
	}
}
// 子句: (x 取值 a) 或 (y 取值 b)
void add(int x,int a,int y,int b){
	g[a?x+n:x].push_back(b?y:y+n); // x 不取 a 则 y 取 b
	g[b?y+n:y].push_back(a?x:x+n); // y 不取 b 则 x 取 a
}
bool solve(){
	for(int i=1;i<=2*n;i++){
		if(!dfn[i])tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(scc[i]==scc[i+n])return 0;
		ans[i]=scc[i]<scc[i+n];
	}
	return 1;
}
void init(int _n){
	n=_n;
	tim=tp=cnt=0;
	for(int i=1;i<=2*n;i++){
		g[i].clear();
		dfn[i]=0;
	}
}
