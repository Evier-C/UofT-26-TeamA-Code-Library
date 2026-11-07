/**
 * Description: 无向图 Tarjan (点 $1..n$, 边 $1..m$), 一次 DFS 同时求:
 * (1) 割点 cut[u] 与点双连通分量 vb[1..vc] (每个点双的点集, 割点会
 * 属于多个点双; 孤立点单独成一个点双). 根是割点当且仅当它在
 * DFS 树上有至少两个儿子.
 * (2) 桥 bri[id] 与边双连通分量 eb[u] (编号 $1..ec$). 用边编号判断
 * 是否走回父边, 所以重边能正确处理. 自环不影响结果.
 * 只需要其中一个时, 删掉另一部分的栈和代码即可.
 * 圆方树 T: 圆点 $1..n$, 第 $i$ 个点双为方点 $n+i$, 向点双内每个点连边;
 * 孤立点也有自己的方点 (只连它一个). 割点等价于圆方树上度数至少 2.
 * 缩点树 E2: 每个边双一个点, 每条桥连一条边 (图不连通时为森林).
 * Usage: init(n,m); // 第 i 条边 (u,v):
 * g[u].push_back({v,i}),g[v].push_back({u,i});
 * for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,0,i);
 * buildRS(n); // 圆方树 T[1..n+vc]
 * buildBT(n); // 缩点树 E2[1..ec], 点 u 对应 eb[u]
 * Time: O(n+m)
 */
#pragma once

const int N=2e5+5,M=4e5+5;
vector<pair<int,int>>g[N]; // {v,边编号}
vector<int>T[N*2],E2[N]; // 圆方树, 边双缩点树
int dfn[N],low[N],tim,s1[N],t1,s2[N],t2;
bool cut[N],bri[M];
int vc,ec,eb[N];vector<int>vb[N];
// in 为进入 u 的边编号, rt 为本次 DFS 的根
void tarjan(int u,int in,int rt){
	dfn[u]=low[u]=++tim,s1[++t1]=s2[++t2]=u;
	int ch=0;
	for(auto[v,id]:g[u]){
		if(!dfn[v]){
			tarjan(v,id,rt),low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u])bri[id]=1;
			if(low[v]>=dfn[u]){ // 弹出一个点双
				if(++ch>1||u!=rt)cut[u]=1;
				vb[++vc].clear();int x;
				do x=s1[t1--],vb[vc].push_back(x);while(x!=v);
				vb[vc].push_back(u);
			}
		}else if(id!=in)low[u]=min(low[u],dfn[v]);
	}
	if(u==rt){if(!ch)vb[++vc]={u};t1=0;}
	if(low[u]==dfn[u]){ // 弹出一个边双
		ec++;int x;
		do x=s2[t2--],eb[x]=ec;while(x!=u);
	}
}
void buildRS(int n){
	for(int i=1;i<=n+vc;i++)T[i].clear();
	for(int i=1;i<=vc;i++)for(int x:vb[i])
		T[n+i].push_back(x),T[x].push_back(n+i);
}
void buildBT(int n){ // 每条桥两个方向各遍历一次
	for(int i=1;i<=ec;i++)E2[i].clear();
	for(int u=1;u<=n;u++)for(auto[v,id]:g[u])
		if(bri[id])E2[eb[u]].push_back(eb[v]);
}
void init(int n,int m){
	for(int i=1;i<=n;i++)g[i].clear(),dfn[i]=cut[i]=0;
	for(int i=1;i<=m;i++)bri[i]=0;
	tim=t1=t2=vc=ec=0;
}
