/**
 * Description: Kahn 拓扑排序. 求字典序最小的拓扑序: 把 queue 换成
 * priority\_queue$<$int,vector$<$int$>$,greater$<$int$>>$. 对象必须是全局变量.
 * Usage: TP.init(n); // 多组数据每组调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v;
 *   TP.g[u].push_back(v); // 边 u 到 v
 * }
 * if(TP.topo(n)){ // 1 表示是 DAG
 *   for(int i=1;i<=n;i++) cout<<TP.ord[i]<<' ';
 * }else{
 *   // 有环: 只有 TP.ord[1..TP.cnt] 有效
 * }
 * Topo TP2; // 第二个对象 (全局)
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
