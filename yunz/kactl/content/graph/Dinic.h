/**
 * Description: 最大流 Dinic, 可输出各边流量, 最小割, 二分图匹配.
 * 数组大, 对象必须是全局 (或 static) 的; 已定义 D, 可再定义 Dinic D2;
 * 点 $1..n$, 容量 ll. N 为点数上限, M 为边数上限的 2 倍.
 * Usage: D.init(n); // 每组数据先调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v>>c;
 *   id[i]=D.add(u,v,c); // 有向边, 返回编号
 * }
 * // 无向边: D.add(u,v,c); D.add(v,u,c);
 * cout<<D.dinic(s,t)<<endl; // 最大流
 * // 边 e 的流量 D.cap[e^1], 原容量 D.cap[e]+D.cap[e^1]
 * for(int i=1;i<=m;i++) cout<<D.cap[id[i]^1]<<' ';
 * // 最小割: D.dep[v] 非 0 的点在 S 侧, 割边见 MinCut.h
 * for(int v=1;v<=n;v++) if(D.dep[v]) cout<<v<<' ';
 * // 二分图匹配: 左 1..L, 右 L+1..L+R, s=L+R+1, t=L+R+2
 * D.init(L+R+2);
 * for(int i=1;i<=L;i++) D.add(s,i,1);
 * for(int j=1;j<=R;j++) D.add(L+j,t,1);
 * for(int k=1;k<=K;k++) id[k]=D.add(a[k],L+b[k],1);
 * int ans=D.dinic(s,t); // 最大匹配数
 * for(int k=1;k<=K;k++) // 满流的边是匹配边
 *   if(!D.cap[id[k]]) cout<<a[k]<<' '<<b[k]<<endl;
 * Time: O(V^2 E), 单位容量 O(E \sqrt{E}), 二分图 O(E \sqrt{V})
 */
#pragma once

struct Dinic{
	static const int N=10005; // 点数
	static const int M=200005; // 边数, 含反向边要开 2 倍
	static constexpr ll INF=1e18;
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
}D;
