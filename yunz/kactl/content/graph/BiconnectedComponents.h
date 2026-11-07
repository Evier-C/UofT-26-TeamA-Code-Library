/**
 * Description: 无向图 Tarjan: 割点, 点双, 桥, 边双, 圆方树, 边双缩点树.
 * 允许重边和自环. 孤立点单独成一个点双 (圆方树上也有自己的方点).
 * 递归深度可达 $n$, 要开大栈. 对象必须是全局变量.
 * Usage: B.init(n,m); // 多组数据每组调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v; // 第 i 条边
 *   B.g[u].push_back({v,i});
 *   B.g[v].push_back({u,i});
 * }
 * for(int i=1;i<=n;i++) if(!B.dfn[i]) B.tarjan(i,0,i);
 * B.cut[u]; // u 是否割点
 * B.vb[k]; // 第 k 个点双的点集, k=1..B.vc
 * B.bri[i]; // 第 i 条边是否桥
 * B.eb[u]; // u 所在边双编号, 1..B.ec
 * B.buildRS(n); // 圆方树 B.T[1..n+B.vc], 方点 n+k 连 vb[k]
 * B.buildBT(n); // 边双缩点树 B.E2[1..B.ec], 每条桥一条边
 * BCC B2; // 第二个对象 (全局)
 * Time: O(n+m)
 */
#pragma once

struct BCC{
	static const int N=2e5+5,M=4e5+5;
	vector<pair<int,int>>g[N]; // {v,边编号}
	vector<int>T[N*2],E2[N]; // 圆方树, 边双缩点树
	int dfn[N],low[N],tim;
	int s1[N],t1,s2[N],t2; // 点双的栈, 边双的栈
	bool cut[N],bri[M];
	int vc,ec,eb[N];
	vector<int>vb[N];
	// in 为进入 u 的边编号, rt 为本次 DFS 的根
	void tarjan(int u,int in,int rt){
		dfn[u]=low[u]=++tim;
		s1[++t1]=u;
		s2[++t2]=u;
		int ch=0;
		for(auto[v,id]:g[u]){
			if(!dfn[v]){
				tarjan(v,id,rt);
				low[u]=min(low[u],low[v]);
				if(low[v]>dfn[u])bri[id]=1;
				if(low[v]>=dfn[u]){ // 弹出一个点双
					ch++;
					if(u!=rt||ch>1)cut[u]=1;
					vb[++vc].clear();
					int x;
					do{
						x=s1[t1--];
						vb[vc].push_back(x);
					}while(x!=v);
					vb[vc].push_back(u);
				}
			}else if(id!=in){
				low[u]=min(low[u],dfn[v]);
			}
		}
		if(u==rt){
			if(!ch)vb[++vc]={u}; // 孤立点
			t1=0;
		}
		if(low[u]==dfn[u]){ // 弹出一个边双
			ec++;
			int x;
			do{
				x=s2[t2--];
				eb[x]=ec;
			}while(x!=u);
		}
	}
	void buildRS(int n){
		for(int i=1;i<=n+vc;i++)T[i].clear();
		for(int i=1;i<=vc;i++){
			for(int x:vb[i]){
				T[n+i].push_back(x);
				T[x].push_back(n+i);
			}
		}
	}
	void buildBT(int n){ // 每条桥两个方向各遍历一次
		for(int i=1;i<=ec;i++)E2[i].clear();
		for(int u=1;u<=n;u++){
			for(auto[v,id]:g[u]){
				if(bri[id])E2[eb[u]].push_back(eb[v]);
			}
		}
	}
	void init(int n,int m){
		for(int i=1;i<=n;i++){
			g[i].clear();
			dfn[i]=cut[i]=0;
		}
		for(int i=1;i<=m;i++)bri[i]=0;
		tim=t1=t2=vc=ec=0;
	}
}B;
