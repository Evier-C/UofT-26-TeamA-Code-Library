/**
 * Description: 基环树找环, 都非递归. 有向: 每个点一条出边 $a[i]$
 * (函数图); 无向: $n$ 点 $n$ 条边, 允许二元环 (重边) 和自环, 森林时
 * 按 bel 分别处理. 无向常见用法: 断环边 ce[k][0] 做两次树形 DP, 或
 * 树上 DP 后在环上破环成链 + 单调队列 (基环树直径).
 * 对象必须是全局变量.
 * Usage: // 有向
 * for(int i=1;i<=n;i++) cin>>FG.a[i];
 * FG.solve(n); // 多组数据直接重新调用
 * // 环 FG.cyc[1..FG.cnt], 按出边顺序
 * // FG.rt[u]: 第一个到达的环上点, FG.dep[u]: 步数
 * // FG.bel[u]: 环编号, FG.pos[u]: rt[u] 在环中下标
 * vector<int>\&c=FG.cyc[FG.bel[u]];
 * int len=c.size();
 * // u 走 k 步 (k 不小于 dep[u]):
 * int v=c[(FG.pos[u]+k-FG.dep[u])\%len];
 * // 无向
 * PT.init(n); // 多组数据每组调用
 * for(int i=1;i<=n;i++){
 *   cin>>u>>v;
 *   PT.addE(u,v); // 第 i 条边
 * }
 * PT.solve(n);
 * // PT.on[u]: 是否环上点; PT.cyc[k]: 环上点按顺序
 * // PT.ce[k][j]: cyc[k][j] 到下一个点的边编号
 * // PT.rt, PT.dep, PT.bel, PT.pos 同有向
 * for(int i=n;i>=1;i--){ // ord 倒序即自底向上
 *   int u=PT.ord[i];
 *   if(PT.fa[u]) f[PT.fa[u]]+=f[u]; // fa: 往环方向的父亲
 * }
 * FuncGraph FG2; PseudoTree PT2; // 第二个对象 (全局)
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
