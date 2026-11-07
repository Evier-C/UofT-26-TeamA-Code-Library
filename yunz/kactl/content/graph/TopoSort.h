/**
 * Description: Kahn 拓扑排序 (BFS), 点 $1..n$. 结构体 Topo, 全局对象 TP.
 * 输入: 有向边存在 TP.g[u] 中. init(n) 清空 g.
 * topo(n): 是 DAG 返回 1, 拓扑序在 ord[1..n] (所有边从前指向后);
 * 有环返回 0, 此时只有 ord[1..cnt] 有效, 环上的点和环能到达的点都
 * 不会出现. 入度 deg 在函数内计算, 不用手动维护.
 * 字典序最小的拓扑序: 把 queue 换成小根堆
 * priority\_queue$<$int,vector$<$int$>$,greater$<$int$>>$.
 * 对象很大, 必须是全局 (或 static) 变量; 要第二个就在全局写 Topo TP2;
 * Usage: TP.init(n); // 多组数据每组调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v;
 *   TP.g[u].push_back(v); // 边 u 到 v
 * }
 * if(TP.topo(n)){
 *   for(int i=1;i<=n;i++) cout<<TP.ord[i]<<' ';
 * }else{
 *   // 有环
 * }
 * Time: O(n+m)
 */
#pragma once

struct Topo{
	static const int N=2e5+5;
	vector<int>g[N];
	int deg[N],ord[N],cnt;
	void init(int n){
		for(int i=1;i<=n;i++)g[i].clear();
	}
	bool topo(int n){
		for(int i=1;i<=n;i++)deg[i]=0;
		for(int u=1;u<=n;u++){
			for(int v:g[u])deg[v]++;
		}
		queue<int>q;
		cnt=0;
		for(int i=1;i<=n;i++){
			if(!deg[i])q.push(i);
		}
		while(!q.empty()){
			int u=q.front();
			q.pop();
			ord[++cnt]=u;
			for(int v:g[u]){
				deg[v]--;
				if(!deg[v])q.push(v);
			}
		}
		return cnt==n;
	}
}TP;
