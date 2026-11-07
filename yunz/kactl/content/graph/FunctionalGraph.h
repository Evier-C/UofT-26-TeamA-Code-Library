/**
 * Description: 基环树. 两个独立的结构体, 都非递归.
 * (1) 有向: 内向基环树森林 (函数图), 每个点 $i$ 恰有一条出边指向 $a[i]$,
 * 点 $1..n$, $1 \le a[i] \le n$. 结构体 FuncGraph, 全局对象 FG.
 * 填好 FG.a[1..n] 后 solve(n) 求出:
 * cyc[1..cnt]: 每个环上的点, 按出边顺序 (cyc[k][j] 的下一个点是
 * cyc[k][(j+1)\%len], len 为环长 cyc[k].size()).
 * rt[u]: 从 $u$ 出发第一个到达的环上点 (环上点为自己);
 * dep[u]: $u$ 到 rt[u] 的步数 (尾巴长度, 环上点为 0);
 * bel[u]: 所在环的编号; pos[u]: rt[u] 在 cyc[bel[u]] 中的下标.
 * 从 $u$ 走 $k$ 步 ($k \ge$ dep[u]) 到达
 * cyc[bel[u]][(pos[u]+k-dep[u])\%len]; $k <$ dep[u] 时要用倍增.
 * (2) 无向: 基环树 / 基环树森林, $n$ 个点 $n$ 条边, 每个连通块恰有一个
 * 环 (允许重边构成的二元环和自环). 结构体 PseudoTree, 全局对象 PT.
 * init(n) 清空, addE(u,v) 加第 $1..m$ 条边, g[u] 存 \{v, 边编号\}.
 * solve(n): 拓扑删叶子 (反复删度数为 1 的点), 剩下的恰好是环上点
 * (on[u] 为 1); 再沿环走一圈. 结果: cyc[1..cnt] 为每个连通块的环,
 * 按环上顺序; ce[k][j] 为连接 cyc[k][j] 和 cyc[k][(j+1)\%len] 的
 * 边编号. 每个点: rt[u] 为它所在的树挂在哪个环上点 (环上点为自己),
 * dep[u] 为到环的距离, bel[u] 为环编号, fa[u] 为往环方向的父亲
 * (环上点为 0), pos[u] 为环上点在 cyc[bel[u]] 中的下标.
 * ord[1..n] 是从环往外的 BFS 序, 倒序遍历即为自底向上, 可做树形 DP.
 * 常见用法: 断开一条环边 ce[k][0] 得到一棵树, 分别以两个端点为根
 * 做两次树形 DP (如基环树上的最大独立集); 或者先对每个环上点挂的
 * 树做 DP, 再在环上做 DP / 破环成链 + 单调队列 (如基环树直径:
 * 树内直径与环上 $d_i + d_j + $ 环上距离 取最大). 基环树森林按
 * bel 对每个连通块分别处理.
 * 对象很大, 必须是全局 (或 static) 变量; 第二个: 全局写 FuncGraph FG2;
 * 或 PseudoTree PT2;
 * Usage: // 有向
 * for(int i=1;i<=n;i++) cin>>FG.a[i];
 * FG.solve(n); // 多组数据直接重新调用
 * bool onCycle=(FG.dep[u]==0);
 * int len=FG.cyc[FG.bel[u]].size(); // u 所在环长
 * // 无向
 * PT.init(n); // 多组数据每组调用
 * for(int i=1;i<=n;i++){
 *   cin>>u>>v;
 *   PT.addE(u,v);
 * }
 * PT.solve(n);
 * for(int i=n;i>=1;i--){ // 自底向上
 *   int u=PT.ord[i];
 *   if(PT.fa[u]) f[PT.fa[u]]+=f[u]; // 示例
 * }
 * for(int k=1;k<=PT.cnt;k++){
 *   vector<int>\&c=PT.cyc[k]; // 环上点按顺序
 * }
 * Time: O(n)
 */
#pragma once

struct FuncGraph{
	static const int N=2e5+5;
	int a[N],vis[N],rt[N],dep[N],bel[N],pos[N],cnt;
	int st[N],tp; // 当前路径上的点
	vector<int>cyc[N];
	void solve(int n){
		cnt=0;
		for(int i=1;i<=n;i++)vis[i]=0;
		// vis: 0 未访问, 1 在当前路径上, 2 已处理完
		for(int i=1;i<=n;i++){
			if(vis[i])continue;
			int u=i;
			tp=0;
			while(!vis[u]){
				vis[u]=1;
				st[++tp]=u;
				u=a[u];
			}
			if(vis[u]==1){ // 找到新环, u 在环上
				cyc[++cnt].clear();
				while(vis[u]==1){
					vis[u]=2;
					rt[u]=u;
					dep[u]=0;
					bel[u]=cnt;
					pos[u]=cyc[cnt].size();
					cyc[cnt].push_back(u);
					u=a[u];
				}
			}
			// 倒着处理路径上不在环上的点
			for(;tp;tp--){
				int v=st[tp];
				if(vis[v]==2)continue;
				vis[v]=2;
				rt[v]=rt[a[v]];
				dep[v]=dep[a[v]]+1;
				bel[v]=bel[a[v]];
				pos[v]=pos[a[v]];
			}
		}
	}
}FG;

struct PseudoTree{
	static const int N=2e5+5;
	int m,deg[N],on[N],rt[N],dep[N],bel[N],fa[N],pos[N];
	int ord[N],cnt;
	vector<pair<int,int>>g[N]; // {v,边编号}
	vector<int>cyc[N],ce[N]; // 环上点, 环上边
	void init(int n){
		m=0;
		for(int i=1;i<=n;i++)g[i].clear();
	}
	void addE(int u,int v){ // 自环会在 g[u] 里出现两次
		m++;
		g[u].push_back({v,m});
		g[v].push_back({u,m});
	}
	void solve(int n){
		queue<int>q;
		for(int i=1;i<=n;i++){
			deg[i]=g[i].size();
			on[i]=1;
			bel[i]=0;
			if(deg[i]==1){
				on[i]=0;
				q.push(i);
			}
		}
		while(!q.empty()){ // 删叶子, 剩下环上点
			int u=q.front();
			q.pop();
			for(auto[v,id]:g[u]){
				if(!on[v])continue;
				deg[v]--;
				if(deg[v]==1){
					on[v]=0;
					q.push(v);
				}
			}
		}
		cnt=0;
		int h=0,t=0; // ord 当作队列
		for(int u=1;u<=n;u++){
			if(!on[u]||bel[u])continue;
			cnt++;
			cyc[cnt].clear();
			ce[cnt].clear();
			int x=u,pe=0; // pe 为走过来的边
			while(1){ // 沿环走一圈
				bel[x]=cnt;
				rt[x]=x;
				dep[x]=fa[x]=0;
				pos[x]=cyc[cnt].size();
				cyc[cnt].push_back(x);
				ord[++t]=x;
				int nx=0,ne=0;
				for(auto[v,id]:g[x]){
					if(on[v]&&id!=pe){
						nx=v;
						ne=id;
						break;
					}
				}
				ce[cnt].push_back(ne);
				if(nx==u)break;
				x=nx;
				pe=ne;
			}
		}
		while(h<t){ // 从环往外 BFS
			int u=ord[++h];
			for(auto[v,id]:g[u]){
				if(on[v]||v==fa[u])continue;
				fa[v]=u;
				rt[v]=rt[u];
				dep[v]=dep[u]+1;
				bel[v]=bel[u];
				ord[++t]=v;
			}
		}
	}
}PT;
