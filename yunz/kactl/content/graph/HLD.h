/**
 * Description: 重链剖分 (点 $1..n$, 根 rt). dfs1 求 fa, dep, siz, son
 * (重儿子); dfs2 求 top (链顶), dfn (新编号), rnk (dfn 的逆). 每条重链
 * 和每棵子树在 dfn 上都是连续区间, 路径拆成 $O(\log n)$ 段区间.
 * 数据结构由用户提供: upd(l,r,v) 给 dfn 区间 $[l, r]$ 加 $v$,
 * qry(l,r) 求区间和, 一般接到线段树上 (按 rnk 建树). 维护 max 等
 * 只需改 qryPath 的合并. 边权: 把边权放到深的那个点上, 路径操作最后
 * 一段改为 $[$dfn[x]$+1$, dfn[y]$]$ (x 等于 y 时跳过), 即不含 LCA.
 * Usage: // 把 upd 和 qry 接到自己的线段树上, 例如:
 * void upd(int l,int r,ll v){update(1,1,n,l,r,v);}
 * ll qry(int l,int r){return query(1,1,n,l,r);}
 * // 多组数据: g[1..n] 清空, tim=0
 * dfs1(rt,0); dfs2(rt,rt); // 线段树第 i 个位置初值 a[rnk[i]]
 * updPath(x,y,v); qryPath(x,y); // 路径
 * updSub(x,v); qrySub(x); lca(x,y); // 子树, LCA
 * Time: 每次路径操作 O(\log^2 n), 子树操作 O(\log n)
 */
#pragma once

const int N=2e5+5;
void upd(int l,int r,ll v);ll qry(int l,int r); // 用户提供
vector<int>g[N];
int fa[N],dep[N],siz[N],son[N],top[N],dfn[N],rnk[N],tim;
void dfs1(int u,int f){
	fa[u]=f,dep[u]=dep[f]+1,siz[u]=1,son[u]=0;
	for(int v:g[u])if(v!=f){
		dfs1(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int t){
	top[u]=t,dfn[u]=++tim,rnk[tim]=u;
	if(son[u])dfs2(son[u],t);
	for(int v:g[u])if(v!=fa[u]&&v!=son[u])dfs2(v,v);
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
		upd(dfn[top[x]],dfn[x],v),x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	upd(dfn[x],dfn[y],v);
}
ll qryPath(int x,int y){
	ll res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		res+=qry(dfn[top[x]],dfn[x]),x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return res+qry(dfn[x],dfn[y]);
}
void updSub(int x,ll v){upd(dfn[x],dfn[x]+siz[x]-1,v);}
ll qrySub(int x){return qry(dfn[x],dfn[x]+siz[x]-1);}
