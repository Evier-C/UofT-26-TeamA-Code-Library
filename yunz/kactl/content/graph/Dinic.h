/**
 * Description: 最大流 Dinic, 链式前向星存图, cnt 从 1 开始,
 * 所以边 $e$ 与反向边 $e \oplus 1$ 成对. 点编号 $1..n$.
 * 输出方案: 原边 $e$ 的流量为 $\text{cap}[e \oplus 1]$ (反向边的剩余容量);
 * 跑完后最后一次 bfs 失败, dep[v] 非 0 的点 (残量网络中 $s$ 能到达)
 * 就是最小割的 $S$ 侧, 割边为 $S$ 侧指向 $T$ 侧的正向边.
 * 二分图匹配: 左 $\to$ 右且满流的边即为匹配边.
 * 无向边 $(u,v,c)$ 用 add(u,v,c), add(v,u,c) 两条有向边.
 * Usage: init(n); // 多组数据每次调用
 * int e=add(u,v,c); // 返回正向边编号, 记下来输出方案
 * ll f=dinic(s,t);
 * ll fe=cap[e^1]; // 边 e 上的流量
 * bool inS=dep[v]; // v 在最小割的 S 侧
 * // 二分图匹配: 左 1..L, 右 L+1..L+R, s=L+R+1, t=L+R+2
 * init(L+R+2); add(s,i,1); id[k]=add(i,L+j,1); add(L+j,t,1);
 * dinic(s,t); // 若 cap[id[k]] 为 0 即满流, 则第 k 条边被选中
 * Time: O(V^2 E), 单位容量 O(E \sqrt{E}), 二分图 O(E \sqrt{V})
 */
#pragma once

const int N=1e4+5,M=2e5+5; // 点数; 边数, 含反向边要开 2 倍
const ll INF=1e18;
int n,S,T,cnt=1,head[N],nxt[M],to[M],dep[N],cur[N];
ll cap[M]; // 剩余容量
void init(int _n){
	n=_n;cnt=1;
	for(int i=1;i<=n;i++)head[i]=0;
}
int add(int u,int v,ll c){ // 有向边 u 到 v, 容量 c
	to[++cnt]=v;cap[cnt]=c;nxt[cnt]=head[u];head[u]=cnt;
	to[++cnt]=u;cap[cnt]=0;nxt[cnt]=head[v];head[v]=cnt;
	return cnt-1;
}
bool bfs(){ // 求出所有 s 可达点的层数, 不提前退出
	for(int i=1;i<=n;i++)dep[i]=0;
	queue<int>q;q.push(S);dep[S]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int e=head[u];e;e=nxt[e])if(cap[e]&&!dep[to[e]]){
			dep[to[e]]=dep[u]+1;q.push(to[e]);
		}
	}
	return dep[T];
}
ll dfs(int u,ll f){
	if(u==T)return f;
	ll res=0;
	for(int&e=cur[u];e;e=nxt[e]){ // 当前弧优化
		int v=to[e];
		if(cap[e]&&dep[v]==dep[u]+1){
			ll d=dfs(v,min(f,cap[e]));
			cap[e]-=d;cap[e^1]+=d;res+=d;f-=d;
			if(!f)break;
		}
	}
	if(!res)dep[u]=0; // 此点已无法增广
	return res;
}
ll dinic(int s,int t){
	S=s;T=t;ll flow=0;
	while(bfs()){
		for(int i=1;i<=n;i++)cur[i]=head[i];
		flow+=dfs(S,INF);
	}
	return flow;
}
