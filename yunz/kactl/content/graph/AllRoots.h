/**
 * Description: 换根 DP 模板, 例子是带边权树上每个点到所有点的距离和
 * 与最远距离. 改别的问题: 换 dfs1 的合并和 dfs2 的转移; 去掉一个儿子
 * 的 max 贡献要记最大和次大. 递归深度可达 $n$, 要开大栈.
 * 对象必须是全局变量.
 * Usage: RR.init(n); // 多组数据每组调用
 * for(int i=1;i<n;i++){
 *   cin>>u>>v>>w;
 *   RR.g[u].push_back({v,w});
 *   RR.g[v].push_back({u,w});
 * }
 * RR.dfs1(1,0); // 以 1 为根, 求子树信息 siz, f, d1, d2
 * RR.ans[1]=RR.f[1]; // 根的答案
 * RR.up[1]=0;
 * RR.dfs2(1,0); // 由父亲推儿子
 * for(int u=1;u<=n;u++) RR.far[u]=max(RR.d1[u],RR.up[u]);
 * // RR.ans[u]: u 到所有点距离和, RR.far[u]: u 的最远距离
 * Reroot RR2; // 第二个对象 (全局)
 * Time: O(n)
 */
#pragma once

struct Reroot{
	static const int N=2e5+5;
	int n,c1[N];
	vector<pair<int,int>>g[N]; // {v,w}
	// siz 子树大小, f 子树内各点到 u 的距离和, ans 全树距离和
	// d1/d2 向下最长/次长链, up 向上最长链, far 最远距离
	ll siz[N],f[N],ans[N],d1[N],d2[N],up[N],far[N];
	void init(int _n){
		n=_n;
		for(int i=1;i<=n;i++)g[i].clear();
	}
	void dfs1(int u,int fa){
		siz[u]=1;
		f[u]=d1[u]=d2[u]=0;
		c1[u]=0;
		for(auto[v,w]:g[u]){
			if(v==fa)continue;
			dfs1(v,u);
			siz[u]+=siz[v];
			f[u]+=f[v]+siz[v]*w;
			ll t=d1[v]+w;
			if(t>d1[u]){
				d2[u]=d1[u];
				d1[u]=t;
				c1[u]=v;
			}else if(t>d2[u]){
				d2[u]=t;
			}
		}
	}
	void dfs2(int u,int fa){
		for(auto[v,w]:g[u]){
			if(v==fa)continue;
			// 根从 u 移到 v: v 子树内的点近 w, 其余点远 w
			ans[v]=ans[u]+(n-2*siz[v])*w;
			// v 向上: 走到 u, 再走 u 的向上链或不经过 v 的向下链
			up[v]=w+max(up[u],c1[u]==v?d2[u]:d1[u]);
			dfs2(v,u);
		}
	}
}RR;
