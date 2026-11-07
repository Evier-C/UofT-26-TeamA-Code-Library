/**
 * Description: 最小费用最大流. 在流量最大的前提下使总费用最小.
 * 做法: 每次用 SPFA 找费用最短的增广路, 沿它推满, 直到 $t$ 不可达.
 * 输入: 点编号 $1..n$, 先 init(n), 再 add(u,v,c,w) 加有向边,
 * 容量 $c$, 单位流量费用 $w$ (都是 ll). 允许负费用, 但不能有负环.
 * 存图为链式前向星, cnt 从 1 开始, 边 $e$ 与反向边 $e \oplus 1$ 成对,
 * 反向边费用为 $-w$. cap[e] 是剩余容量.
 * 函数: add 返回正向边编号; mcmf(s,t) 返回 (最大流, 最小费用).
 * 输出方案:
 * (1) 每条原边的流量: $\text{cap}[e \oplus 1]$, 该边费用为流量乘 $w$.
 * (2) 最小割: 跑完后 dis[v] 小于 INF 的点 (残量网络中 $s$ 能到达)
 * 为 $S$ 侧.
 * (3) 带权二分图匹配: 源点连左部, 右部连汇点, 容量 1 费用 0,
 * 左右边容量 1 费用 $w$; 左到右满流 (cap[e] 为 0) 的边为匹配边.
 * 求最大费用: 费用全取负, 答案再取负. 只要最小费用流 (不要求最大流)
 * 时, 在 mcmf 里当 dis[t] 不小于 0 就停止.
 * 注意: 无向边要 add 两次. N, M 为点数, 边数上限 (每条边占 2 个位置).
 * 全局变量名与 Dinic 等冲突, 不能同时 include. 多组数据每组先 init(n).
 * Usage: init(n); // 每组数据先调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v>>c>>w;
 *   id[i]=add(u,v,c,w); // 记下第 i 条边的编号
 * }
 * auto [f,co]=mcmf(s,t); // 最大流, 最小费用
 * cout<<f<<' '<<co<<endl;
 * for(int i=1;i<=m;i++) cout<<cap[id[i]^1]<<' '; // 各边流量
 * for(int v=1;v<=n;v++) if(dis[v]<INF) cout<<v<<' '; // S 侧
 * // 带权匹配: 左 1..L, 右 L+1..L+R, s=L+R+1, t=L+R+2
 * init(L+R+2);
 * for(int i=1;i<=L;i++) add(s,i,1,0);
 * for(int j=1;j<=R;j++) add(L+j,t,1,0);
 * for(int k=1;k<=K;k++) id[k]=add(a[k],L+b[k],1,w[k]);
 * auto [cntMatch,minCost]=mcmf(s,t);
 * for(int k=1;k<=K;k++) // 满流的边是匹配边
 *   if(!cap[id[k]]) cout<<a[k]<<' '<<b[k]<<endl;
 * Time: O(F \cdot VE), $F$ 为最大流, 实际远快于此.
 */
#pragma once

const int N=5005,M=1e5+5; // 点数; 边数, 含反向边要开 2 倍
const ll INF=1e18;
int n,cnt=1,head[N],nxt[M],to[M],pre[N]; // pre[v]: 到 v 的边
ll cap[M],cost[M],dis[N],fl[N]; // fl: 路径上的最小容量
bool inq[N];
void init(int _n){
	n=_n;
	cnt=1;
	for(int i=1;i<=n;i++)head[i]=0;
}
void addOne(int u,int v,ll c,ll w){
	cnt++;
	to[cnt]=v;
	cap[cnt]=c;
	cost[cnt]=w;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
int add(int u,int v,ll c,ll w){ // 返回正向边编号
	addOne(u,v,c,w);
	addOne(v,u,0,-w);
	return cnt-1;
}
bool spfa(int s,int t){
	for(int i=1;i<=n;i++){
		dis[i]=INF;
		inq[i]=0;
	}
	queue<int>q;
	q.push(s);
	dis[s]=0;
	fl[s]=INF;
	inq[s]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int e=head[u];e;e=nxt[e]){
			int v=to[e];
			if(cap[e]&&dis[u]+cost[e]<dis[v]){
				dis[v]=dis[u]+cost[e];
				pre[v]=e;
				fl[v]=min(fl[u],cap[e]);
				if(!inq[v]){
					inq[v]=1;
					q.push(v);
				}
			}
		}
	}
	return dis[t]<INF;
}
pair<ll,ll>mcmf(int s,int t){
	ll flow=0,c=0;
	while(spfa(s,t)){
		ll f=fl[t];
		flow+=f;
		c+=f*dis[t];
		for(int v=t;v!=s;v=to[pre[v]^1]){
			cap[pre[v]]-=f;
			cap[pre[v]^1]+=f;
		}
	}
	return {flow,c};
}
