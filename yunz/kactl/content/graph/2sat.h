/**
 * Description: 2-SAT. N 为变量数上限 (数组开 2N). 递归深度可达 $2n$,
 * 要开大栈. 对象必须是全局变量.
 * Usage: TS.init(n); // 变量 1..n, 多组数据每组调用
 * for(int i=1;i<=m;i++){
 *   cin>>x>>a>>y>>b; // a,b 为 0 或 1
 *   TS.add(x,a,y,b); // 子句: x 取 a 或 y 取 b
 * }
 * TS.add(x,1,x,1); // 强制 x 为真
 * TS.add(x,0,y,0); // x 和 y 不能同时为真
 * bool ok=TS.solve(); // 0 表示无解
 * if(ok) for(int i=1;i<=n;i++) cout<<TS.ans[i]<<' '; // 1 为真
 * TwoSat TS2; // 第二个对象 (全局)
 * Time: O(n+m)
 */
#pragma once

struct TwoSat{
	static const int N=2e5+5; // 变量数, 点数为 2N
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
}TS;
