/**
 * Description: Hierholzer 欧拉路径, 有向或无向, 允许重边和自环.
 * 度数条件不满足或边不连通时 euler() 返回 0. 递归深度可达 $m$,
 * 要开大栈. 对象必须是全局变量.
 * Usage: EU.init(n,0); // 0 无向, 1 有向; 多组数据每组调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v;
 *   EU.addE(u,v); // 第 i 条边
 * }
 * if(EU.euler()){
 *   for(int i=1;i<=m+1;i++) cout<<EU.path[i]<<' '; // 点序列
 *   // EU.ep[i] 为第 i 步走的边, 连接 path[i] 和 path[i+1]
 *   bool circuit=(EU.path[1]==EU.path[m+1]); // 是否回路
 * }
 * Euler EU2; // 第二个对象 (全局)
 * Time: O(n+m)
 */
#pragma once

struct Euler{
	static const int N=1e5+5,M=2e5+5;
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
}EU;
