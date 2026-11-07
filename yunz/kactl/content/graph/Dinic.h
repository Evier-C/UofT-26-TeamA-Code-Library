/**
 * Description: 最大流 Dinic. 求有向图从 $s$ 到 $t$ 的最大流, 并能输出方案.
 * 输入: 点编号 $1..n$, 先 init(n), 再用 add(u,v,c) 加有向边 ($c$ 为 ll 容量).
 * 存图为链式前向星 head/nxt/to/cap, cnt 从 1 开始, 所以第一条边编号为 2,
 * 边 $e$ 与反向边 $e \oplus 1$ 成对. cap[e] 是剩余容量.
 * 函数: add 返回正向边编号 (要输出方案就记下来); dinic(s,t) 返回最大流.
 * 输出方案:
 * (1) 每条原边的流量: $\text{cap}[e \oplus 1]$ (反向边的剩余容量);
 * 原容量为 $\text{cap}[e] + \text{cap}[e \oplus 1]$.
 * (2) 最小割: 跑完后 dep[v] 非 0 的点就是残量网络中 $s$ 能到达的点,
 * 即 $S$ 侧; 割边为 $S$ 侧指向 $T$ 侧的正向边, 一定满流, 容量和等于最大流
 * (见 MinCut.h).
 * (3) 二分图匹配: 源点连左部, 右部连汇点, 左右之间容量 1;
 * 跑完后左到右的边若满流 (cap[e] 为 0) 就是匹配边.
 * 注意: 无向边 $(u,v,c)$ 要调用 add(u,v,c) 和 add(v,u,c).
 * N 为点数上限, M 为边数上限 (每条边占 2 个位置).
 * 全局变量名 (N, M, n, cnt, head ...) 与 MinCostMaxFlow 等冲突,
 * 不能同时 include. 多组数据每组先 init(n).
 * Usage: init(n); // 每组数据先调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v>>c;
 *   id[i]=add(u,v,c); // 记下第 i 条边的编号
 * }
 * cout<<dinic(s,t)<<endl; // 最大流
 * for(int i=1;i<=m;i++) cout<<cap[id[i]^1]<<' '; // 各边流量
 * for(int v=1;v<=n;v++) if(dep[v]) cout<<v<<' '; // 最小割 S 侧
 * // 二分图匹配: 左 1..L, 右 L+1..L+R, s=L+R+1, t=L+R+2
 * init(L+R+2);
 * for(int i=1;i<=L;i++) add(s,i,1);
 * for(int j=1;j<=R;j++) add(L+j,t,1);
 * for(int k=1;k<=K;k++) id[k]=add(a[k],L+b[k],1); // 边 a 到 b
 * int ans=dinic(s,t);
 * for(int k=1;k<=K;k++) // 满流的边是匹配边
 *   if(!cap[id[k]]) cout<<a[k]<<' '<<b[k]<<endl;
 * Time: O(V^2 E), 单位容量 O(E \sqrt{E}), 二分图 O(E \sqrt{V})
 */
#pragma once

const int N=1e4+5,M=2e5+5; // 点数; 边数, 含反向边要开 2 倍
const ll INF=1e18;
int n,S,T,cnt=1,head[N],nxt[M],to[M],dep[N],cur[N];
ll cap[M]; // 剩余容量
void init(int _n){
	n=_n;
	cnt=1;
	for(int i=1;i<=n;i++)head[i]=0;
}
void addOne(int u,int v,ll c){
	cnt++;
	to[cnt]=v;
	cap[cnt]=c;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
int add(int u,int v,ll c){ // u 到 v, 容量 c, 返回编号
	addOne(u,v,c);
	addOne(v,u,0);
	return cnt-1;
}
bool bfs(){ // 求出所有 s 可达点的层数, 不提前退出
	for(int i=1;i<=n;i++)dep[i]=0;
	queue<int>q;
	q.push(S);
	dep[S]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int e=head[u];e;e=nxt[e]){
			int v=to[e];
			if(cap[e]&&!dep[v]){
				dep[v]=dep[u]+1;
				q.push(v);
			}
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
			cap[e]-=d;
			cap[e^1]+=d;
			res+=d;
			f-=d;
			if(!f)break;
		}
	}
	if(!res)dep[u]=0; // 此点已无法增广
	return res;
}
ll dinic(int s,int t){
	S=s;
	T=t;
	ll flow=0;
	while(bfs()){
		for(int i=1;i<=n;i++)cur[i]=head[i];
		flow+=dfs(S,INF);
	}
	return flow;
}
