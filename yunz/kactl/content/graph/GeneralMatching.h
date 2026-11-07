/**
 * Description: 一般图最大匹配 (带花树).
 * 数组大, 对象必须是全局 (或 static) 的; 已定义 BM, 可再定义 Blossom BM2;
 * 点 $1..n$, 可有自环, 重边. N 为点数上限, M 为边数上限的 2 倍.
 * Usage: BM.init(n); // 每组数据先调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v;
 *   BM.add(u,v); // 无向边, 只加一次
 * }
 * cout<<BM.solve()<<endl; // 最大匹配数
 * for(int u=1;u<=n;u++) // u 匹配 BM.mt[u], 0 为未匹配
 *   if(BM.mt[u]>u) cout<<u<<' '<<BM.mt[u]<<endl;
 * Time: O(n^3)
 */
#pragma once

struct Blossom{
	static const int N=1005; // 点数
	static const int M=200005; // 边数, 每条边存两次
	int n,cnt,head[N],nxt[M],to[M];
	int mt[N],pre[N],fa[N],vis[N],dfn[N],tim;
	queue<int>q;
	void init(int _n){
		n=_n;
		cnt=0;
		tim=0;
		for(int i=0;i<=n;i++){
			head[i]=0;
			mt[i]=0;
			dfn[i]=0;
		}
		fa[0]=0;
	}
	void addOne(int u,int v){
		cnt++;
		to[cnt]=v;
		nxt[cnt]=head[u];
		head[u]=cnt;
	}
	void add(int u,int v){
		addOne(u,v);
		addOne(v,u);
	}
	int find(int x){
		if(fa[x]==x)return x;
		return fa[x]=find(fa[x]);
	}
	int lca(int x,int y){ // 两个偶点在交错树上的最近公共花
		tim++;
		x=find(x);
		y=find(y);
		while(dfn[x]!=tim){
			dfn[x]=tim;
			x=find(pre[mt[x]]);
			if(y)swap(x,y);
		}
		return x;
	}
	void blossom(int x,int y,int w){ // x 到花根 w 的路径缩进花
		while(find(x)!=w){
			pre[x]=y;
			y=mt[x];
			if(vis[y]==2){ // 花里的奇点变成偶点
				vis[y]=1;
				q.push(y);
			}
			if(find(x)==x)fa[x]=w;
			if(find(y)==y)fa[y]=w;
			x=pre[y];
		}
	}
	bool aug(int s){ // 从未匹配点 s 找增广路
		for(int i=1;i<=n;i++){
			fa[i]=i;
			vis[i]=0;
			pre[i]=0;
		}
		while(!q.empty())q.pop();
		q.push(s);
		vis[s]=1;
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int e=head[u];e;e=nxt[e]){
				int v=to[e];
				if(find(u)==find(v)||vis[v]==2)continue;
				if(vis[v]==1){ // u, v 都是偶点, 出现奇环
					int w=lca(u,v);
					blossom(u,v,w);
					blossom(v,u,w);
					continue;
				}
				vis[v]=2;
				pre[v]=u;
				if(!mt[v]){ // 找到增广路, 沿 pre 翻转
					int x=v;
					while(x){
						int y=mt[pre[x]];
						mt[x]=pre[x];
						mt[pre[x]]=x;
						x=y;
					}
					return true;
				}
				vis[mt[v]]=1;
				q.push(mt[v]);
			}
		}
		return false;
	}
	int solve(){
		int res=0;
		for(int i=1;i<=n;i++){
			if(!mt[i]&&aug(i))res++;
		}
		return res;
	}
}BM;
