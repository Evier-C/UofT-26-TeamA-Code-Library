/**
 * Description: Hierholzer 求欧拉路径/回路 (点 $1..n$, 边 $1..m$), 有向或
 * 无向, 允许重边和自环. 存在条件: 无向图奇度点为 0 或 2 个 (2 个时从
 * 奇度点出发); 有向图所有点出度等于入度, 或恰有一个点出度比入度大 1
 * (起点) 且一个点入度比出度大 1. 另外所有边必须连通: 跑完后若
 * len $\ne m+1$ 也无解. 只要回路时额外检查起点等于终点即可.
 * Usage: init(n,1); // 1 有向, 0 无向
 * addE(u,v); // 依次加边, 边编号 1..m
 * if(euler()) path[1..m+1] 为点序列, ep[1..m] 为边编号
 * Time: O(n+m)
 */
#pragma once

const int N=1e5+5,M=2e5+5;
int n,m,dir,cur[N],deg[N],path[M],len,ep[M],le;
bool vis[M];vector<pair<int,int>>g[N]; // {v,边编号}
void init(int _n,int d){
	n=_n,dir=d,m=len=le=0;
	for(int i=1;i<=n;i++)g[i].clear(),cur[i]=deg[i]=0;
}
// 有向图 deg 为出度减入度, 无向图 deg 为度数
void addE(int u,int v){
	m++,vis[m]=0,g[u].push_back({v,m});
	if(dir)deg[u]++,deg[v]--;
	else g[v].push_back({u,m}),deg[u]++,deg[v]++;
}
void dfs(int u){
	while(cur[u]<(int)g[u].size()){
		auto[v,id]=g[u][cur[u]++];
		if(vis[id])continue;
		vis[id]=1,dfs(v),ep[++le]=id;
	}
	path[++len]=u;
}
bool euler(){
	int s=1,c=0;
	for(int i=n;i>=1;i--)if(g[i].size())s=i;
	for(int i=1;i<=n;i++){
		if(dir&&deg[i]==1)c++,s=i;
		else if(dir&&deg[i]!=0&&deg[i]!=-1)return 0;
		if(!dir&&deg[i]%2)c++,s=i;
	}
	if(c>(dir?1:2))return 0;
	dfs(s);
	reverse(path+1,path+len+1),reverse(ep+1,ep+le+1);
	return len==m+1;
}
