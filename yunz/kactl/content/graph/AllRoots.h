/**
 * Description: 换根 DP 模板 (树, 点 $1..n$, 带边权). 例子同时求两件事:
 * ans[u] $= \sum_v dist(u, v)$, far[u] $= \max_v dist(u, v)$.
 * dfs1 自底向上求子树信息 (以 1 为根); dfs2 自顶向下, 用父亲的
 * 答案推出儿子的答案. 去掉儿子 v 的贡献: 可减的量 (和) 直接减,
 * 不可减的量 (max) 记最大值和次大值, 或用前缀/后缀合并.
 * Usage: for(i=1..n) g[i].clear(); // 多组数据
 * g[u].push_back({v,w}),g[v].push_back({u,w});
 * dfs1(1,0); ans[1]=f[1]; up[1]=0; dfs2(1,0);
 * far[u]=max(d1[u],up[u]);
 * Time: O(n)
 */
#pragma once

const int N=2e5+5;
int n,c1[N];
vector<pair<int,int>>g[N]; // {v,w}
// siz 子树大小, f 子树内各点到 u 的距离和, ans 全树距离和
// d1/d2 向下最长/次长链, c1 最长链所在儿子, up 向上最长链
ll siz[N],f[N],ans[N],d1[N],d2[N],up[N],far[N];
void dfs1(int u,int fa){
	siz[u]=1,f[u]=d1[u]=d2[u]=c1[u]=0;
	for(auto[v,w]:g[u])if(v!=fa){
		dfs1(v,u);
		siz[u]+=siz[v],f[u]+=f[v]+siz[v]*w;
		ll t=d1[v]+w;
		if(t>d1[u])d2[u]=d1[u],d1[u]=t,c1[u]=v;
		else if(t>d2[u])d2[u]=t;
	}
}
void dfs2(int u,int fa){
	for(auto[v,w]:g[u])if(v!=fa){
		// 根从 u 移到 v: v 子树内的点近 w, 其余点远 w
		ans[v]=ans[u]+(n-2*siz[v])*w;
		up[v]=w+max(up[u],c1[u]==v?d2[u]:d1[u]);
		dfs2(v,u);
	}
}
