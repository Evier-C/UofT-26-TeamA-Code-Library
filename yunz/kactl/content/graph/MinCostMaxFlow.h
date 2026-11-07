/**
 * Description: 最小费用最大流 (SPFA), 可有负费用, 不能有负环.
 * 数组大, 对象必须是全局 (或 static) 的; 已定义 MF, 可再定义 MCMF MF2;
 * 可与 Dinic.h 同时使用. 点 $1..n$, 容量和费用为 ll.
 * N 为点数上限, M 为边数上限的 2 倍.
 * Usage: MF.init(n); // 每组数据先调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v>>c>>w; // 容量 c, 单位费用 w
 *   id[i]=MF.add(u,v,c,w); // 有向边, 返回编号
 * }
 * // 无向边要 add 两次; 求最大费用: 费用取负, 答案取负
 * auto [f,co]=MF.mcmf(s,t); // 最大流, 最小费用
 * cout<<f<<' '<<co<<endl;
 * for(int i=1;i<=m;i++) cout<<MF.cap[id[i]^1]<<' '; // 各边流量
 * for(int v=1;v<=n;v++) // 最小割 S 侧
 *   if(MF.dis[v]<MF.INF) cout<<v<<' ';
 * // 不要求最大流, 只要费用最小: mcmf 中 dis[t] 不小于 0 时停止
 * // 带权匹配: 左 1..L, 右 L+1..L+R, s=L+R+1, t=L+R+2
 * MF.init(L+R+2);
 * for(int i=1;i<=L;i++) MF.add(s,i,1,0);
 * for(int j=1;j<=R;j++) MF.add(L+j,t,1,0);
 * for(int k=1;k<=K;k++) id[k]=MF.add(a[k],L+b[k],1,wt[k]);
 * auto [cntMatch,minCost]=MF.mcmf(s,t);
 * for(int k=1;k<=K;k++) // 满流的边是匹配边
 *   if(!MF.cap[id[k]]) cout<<a[k]<<' '<<b[k]<<endl;
 * Time: O(F \cdot VE), $F$ 为最大流, 实际远快于此.
 */
#pragma once

struct MCMF{
	static const int N=5005; // 点数
	static const int M=100005; // 边数, 含反向边要开 2 倍
	static constexpr ll INF=1e18;
	// pre[v]: 最短路上进入 v 的边
	int n,cnt=1,head[N],nxt[M],to[M],pre[N];
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
}MF;
