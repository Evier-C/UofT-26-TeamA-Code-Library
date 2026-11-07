/**
 * Description: Hierholzer 求欧拉路径/回路 (每条边恰好走一次), 点 $1..n$,
 * 边按加入顺序编号 $1..m$, 有向图或无向图都可以, 允许重边和自环.
 * init(n,dir): dir 为 1 有向, 0 无向. addE(u,v): 加一条边.
 * euler(): 有欧拉路径返回 1, 点序列在 path[1..m+1], 走过的边编号
 * 依次在 ep[1..m] ($ep[i]$ 连接 $path[i]$ 和 $path[i+1]$).
 * 存在条件: 无向图奇度点为 0 或 2 个 (2 个时从奇度点出发); 有向图所有点
 * 出度等于入度, 或恰有一个点出度比入度大 1 (起点) 且一个点入度比
 * 出度大 1; 并且所有边连通 (跑完后 len 不等于 $m+1$ 即不连通).
 * 不满足时返回 0. 要回路: 再判断 path[1] 等于 path[m+1].
 * 注意: dfs 递归深度可达 $m$, 要开大栈. N 点数, M 边数上限.
 * Usage: init(n,0); // 无向图, 多组数据每组调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v;
 *   addE(u,v); // 第 i 条边
 * }
 * if(euler()){
 *   for(int i=1;i<=m+1;i++) cout<<path[i]<<' ';
 * }
 * Time: O(n+m)
 */
#pragma once

const int N=1e5+5,M=2e5+5;
int n,m,dir,cur[N],deg[N];
int path[M],len,ep[M],le;
bool vis[M]; // 边是否走过
vector<pair<int,int>>g[N]; // {v,边编号}
void init(int _n,int d){
	n=_n;
	dir=d;
	m=len=le=0;
	for(int i=1;i<=n;i++){
		g[i].clear();
		cur[i]=deg[i]=0;
	}
}
// 有向图 deg 为出度减入度, 无向图 deg 为度数
void addE(int u,int v){
	m++;
	vis[m]=0;
	g[u].push_back({v,m});
	if(dir){
		deg[u]++;
		deg[v]--;
	}else{
		g[v].push_back({u,m});
		deg[u]++;
		deg[v]++;
	}
}
void dfs(int u){
	// cur[u] 为当前弧, 保证每条边只扫一次
	while(cur[u]<(int)g[u].size()){
		auto[v,id]=g[u][cur[u]++];
		if(vis[id])continue;
		vis[id]=1;
		dfs(v);
		ep[++le]=id;
	}
	path[++len]=u;
}
bool euler(){
	int s=1,c=0; // s 起点, c 特殊点个数
	for(int i=n;i>=1;i--){
		if(g[i].size())s=i;
	}
	for(int i=1;i<=n;i++){
		if(dir){
			if(deg[i]==1){
				c++;
				s=i;
			}else if(deg[i]!=0&&deg[i]!=-1){
				return 0;
			}
		}else if(deg[i]%2){
			c++;
			s=i;
		}
	}
	if(c>(dir?1:2))return 0;
	dfs(s);
	reverse(path+1,path+len+1);
	reverse(ep+1,ep+le+1);
	return len==m+1;
}
