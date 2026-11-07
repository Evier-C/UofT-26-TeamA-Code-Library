/**
 * Description: 重链剖分, 点 $1..n$, 根 rt. 支持路径加/路径和,
 * 子树加/子树和, 求 LCA, 每次 $O(\log n)$ 段区间. 结构体 HLD,
 * 全局对象 H. 输入: init(n) 清空, 无向树边存在 H.g[u] 中.
 * dfs1(rt,0) 求 fa (父亲), dep (深度, 根为 1), siz (子树大小), son
 * (重儿子, 没有为 0); dfs2(rt,rt) 求 top (所在重链的顶), dfn (新编号,
 * $1..n$), rnk (dfn 的逆, rnk[dfn[u]]$=u$).
 * 每条重链和每棵子树在 dfn 上都是连续区间: 子树 $u$ 为
 * $[$dfn[u], dfn[u]$+$siz[u]$-1]$.
 * 区间数据结构由用户在结构体外提供 (本文件只声明这两个全局函数):
 * upd(l,r,v) 把 dfn 区间 $[l, r]$ 加 $v$, qry(l,r) 求区间和, 一般接到
 * 线段树上, 线段树第 $i$ 个位置的初值为 a[rnk[i]]. 维护 max 等只需改
 * qryPath 里的合并. 边权: 把边权放到深的那个点上, 路径操作的最后
 * 一段改为 $[$dfn[x]$+1$, dfn[y]$]$ (x 等于 y 时跳过), 即不含 LCA.
 * 注意: dfs 递归深度可达 $n$, 链状树要开大栈.
 * 对象很大, 必须是全局 (或 static) 变量; 要第二个就在全局写 HLD H2;
 * (两个对象共用同一对 upd/qry, 需要时复制结构体改名.)
 * Usage: // 结构体外, 把 upd 和 qry 接到自己的线段树上, 例如:
 * void upd(int l,int r,ll v){update(1,1,n,l,r,v);}
 * ll qry(int l,int r){return query(1,1,n,l,r);}
 * // main 里:
 * H.init(n); // 多组数据每组调用
 * for(int i=1;i<n;i++){
 *   cin>>u>>v;
 *   H.g[u].push_back(v);
 *   H.g[v].push_back(u);
 * }
 * H.dfs1(rt,0);
 * H.dfs2(rt,rt);
 * for(int i=1;i<=n;i++) b[i]=a[H.rnk[i]];
 * build(1,1,n); // 用 b 建线段树
 * H.updPath(x,y,v); // 路径加
 * ll s=H.qryPath(x,y); // 路径和
 * H.updSub(x,v); // 子树加
 * ll t=H.qrySub(x); // 子树和
 * int l=H.lca(x,y);
 * Time: 路径操作 O(\log^2 n), 子树操作 O(\log n)
 */
#pragma once

void upd(int l,int r,ll v); // 用户提供
ll qry(int l,int r); // 用户提供
struct HLD{
	static const int N=2e5+5;
	vector<int>g[N];
	int fa[N],dep[N],siz[N],son[N];
	int top[N],dfn[N],rnk[N],tim;
	void init(int n){
		for(int i=1;i<=n;i++)g[i].clear();
		tim=0;
	}
	void dfs1(int u,int f){
		fa[u]=f;
		dep[u]=dep[f]+1;
		siz[u]=1;
		son[u]=0;
		for(int v:g[u]){
			if(v==f)continue;
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])son[u]=v;
		}
	}
	void dfs2(int u,int t){
		top[u]=t;
		dfn[u]=++tim;
		rnk[tim]=u;
		if(son[u])dfs2(son[u],t); // 先走重儿子, 重链连续
		for(int v:g[u]){
			if(v!=fa[u]&&v!=son[u])dfs2(v,v);
		}
	}
	int lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]])swap(x,y);
			x=fa[top[x]];
		}
		return dep[x]<dep[y]?x:y;
	}
	void updPath(int x,int y,ll v){
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]])swap(x,y);
			upd(dfn[top[x]],dfn[x],v);
			x=fa[top[x]];
		}
		if(dep[x]>dep[y])swap(x,y);
		upd(dfn[x],dfn[y],v);
	}
	ll qryPath(int x,int y){
		ll res=0;
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]])swap(x,y);
			res+=qry(dfn[top[x]],dfn[x]);
			x=fa[top[x]];
		}
		if(dep[x]>dep[y])swap(x,y);
		return res+qry(dfn[x],dfn[y]);
	}
	void updSub(int x,ll v){upd(dfn[x],dfn[x]+siz[x]-1,v);}
	ll qrySub(int x){return qry(dfn[x],dfn[x]+siz[x]-1);}
}H;
