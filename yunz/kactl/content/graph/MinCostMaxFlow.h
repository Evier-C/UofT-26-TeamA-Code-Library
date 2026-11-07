/**
 * Description: 最小费用最大流 (SPFA 找最短路, 逐条增广). 链式前向星,
 * cnt 从 1 开始, 边 $e$ 与反向边 $e \oplus 1$ 成对, 点编号 $1..n$.
 * 允许负费用, 但不能有负环. 返回 (最大流, 最小费用).
 * 输出方案: 原边 $e$ 的流量为 $\text{cap}[e \oplus 1]$;
 * 跑完后 dis[v] 小于 INF 的点 (残量网络中 $s$ 能到达) 为最小割的 $S$ 侧.
 * 最小费用二分图匹配: 左 $\to$ 右且满流的边即为匹配边.
 * 求最大费用: 费用取负, 答案再取负.
 * Usage: init(n); // 多组数据每次调用
 * int e=add(u,v,c,w); // 容量 c, 单位费用 w, 记下编号
 * auto [f,co]=mcmf(s,t); // 最大流, 最小费用
 * ll fe=cap[e^1]; // 边 e 上的流量
 * bool inS=dis[v]<INF; // v 在最小割的 S 侧
 * // 带权匹配: s 连左, 右连 t 容量 1 费用 0, 左右边容量 1
 * id[k]=add(i,L+j,1,w); // 若 cap[id[k]] 为 0 则第 k 条边被选中
 * Time: O(F \cdot VE), $F$ 为最大流, 实际远快于此.
 */
#pragma once

const int N=5005,M=1e5+5; // 点数; 边数, 含反向边要开 2 倍
const ll INF=1e18;
int n,cnt=1,head[N],nxt[M],to[M],pre[N];
ll cap[M],cost[M],dis[N],fl[N]; // fl: 路径上的最小容量
bool inq[N];
void init(int _n){
	n=_n;cnt=1;
	for(int i=1;i<=n;i++)head[i]=0;
}
int add(int u,int v,ll c,ll w){ // 返回正向边编号
	to[++cnt]=v;cap[cnt]=c;cost[cnt]=w;
	nxt[cnt]=head[u];head[u]=cnt;
	to[++cnt]=u;cap[cnt]=0;cost[cnt]=-w;
	nxt[cnt]=head[v];head[v]=cnt;
	return cnt-1;
}
bool spfa(int s,int t){
	for(int i=1;i<=n;i++)dis[i]=INF,inq[i]=0;
	queue<int>q;q.push(s);dis[s]=0;fl[s]=INF;inq[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=0;
		for(int e=head[u];e;e=nxt[e]){
			int v=to[e];
			if(cap[e]&&dis[u]+cost[e]<dis[v]){
				dis[v]=dis[u]+cost[e];pre[v]=e;
				fl[v]=min(fl[u],cap[e]);
				if(!inq[v])inq[v]=1,q.push(v);
			}
		}
	}
	return dis[t]<INF;
}
pair<ll,ll>mcmf(int s,int t){
	ll flow=0,c=0;
	while(spfa(s,t)){
		ll f=fl[t];flow+=f;c+=f*dis[t];
		for(int v=t;v!=s;v=to[pre[v]^1])
			cap[pre[v]]-=f,cap[pre[v]^1]+=f;
	}
	return {flow,c};
}
