/**
 * Description: 重链剖分: 路径/子树加和求和, LCA. upd 和 qry 由用户在
 * 结构体外提供 (两个对象共用). 维护 max 等改 qryPath 的合并.
 * 边权: 放到深的点上, 路径最后一段用 $[$dfn[x]$+1$, dfn[y]$]$.
 * 递归深度可达 $n$, 要开大栈. 对象必须是全局变量.
 * Usage: // 结构体外, 接到自己的线段树 (dfn 区间加/求和):
 * void upd(int l,int r,ll v){update(1,1,n,l,r,v);}
 * ll qry(int l,int r){return query(1,1,n,l,r);}
 * // main 里:
 * H.init(n); // 多组数据每组调用
 * for(int i=1;i<n;i++){
 *   cin>>u>>v;
 *   H.g[u].push_back(v);
 *   H.g[v].push_back(u);
 * }
 * H.dfs1(rt,0); // fa, dep, siz, son
 * H.dfs2(rt,rt); // top, dfn, rnk (dfn 的逆)
 * for(int i=1;i<=n;i++) b[i]=a[H.rnk[i]];
 * build(1,1,n); // 用 b 建线段树
 * H.updPath(x,y,v); // 路径加
 * ll s=H.qryPath(x,y); // 路径和
 * H.updSub(x,v); // 子树加, 子树为 [dfn[x],dfn[x]+siz[x]-1]
 * ll t=H.qrySub(x); // 子树和
 * int l=H.lca(x,y);
 * HLD H2; // 第二个对象 (全局)
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
