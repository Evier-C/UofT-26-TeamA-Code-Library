/**
 * Description: 一般图最大匹配, 带花树 (Edmonds blossom). 点编号 $1..n$.
 * 对每个未匹配点 bfs 找增广路, 遇到奇环就缩成一朵花 (并查集 fa).
 * vis 为 1 表示偶点 (可入队), 为 2 表示奇点. 返回匹配数,
 * mt[u] 为 $u$ 匹配的点, 未匹配为 0.
 * Usage: init(n); // 多组数据每次调用
 * add(u,v); // 无向边
 * int res=solve();
 * for(int u=1;u<=n;u++) if(mt[u]>u) cout<<u<<' '<<mt[u]<<endl;
 * Time: O(n^3)
 */
#pragma once

const int N=1005,M=2e5+5; // 点数; 边数, 每条边存两次
int n,cnt,head[N],nxt[M],to[M];
int mt[N],pre[N],fa[N],vis[N],dfn[N],tim;
queue<int>q;
void init(int _n){
	n=_n;cnt=0;tim=0;
	for(int i=0;i<=n;i++)head[i]=mt[i]=dfn[i]=0;
}
void add(int u,int v){
	to[++cnt]=v;nxt[cnt]=head[u];head[u]=cnt;
	to[++cnt]=u;nxt[cnt]=head[v];head[v]=cnt;
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int lca(int x,int y){ // 两个偶点在交错树上的最近公共花
	tim++;x=find(x);y=find(y);
	while(dfn[x]!=tim){
		dfn[x]=tim;
		x=find(pre[mt[x]]);
		if(y)swap(x,y);
	}
	return x;
}
void blossom(int x,int y,int w){ // 把 x 到花根 w 的路径缩进花
	while(find(x)!=w){
		pre[x]=y;y=mt[x];
		if(vis[y]==2)vis[y]=1,q.push(y); // 花里的奇点变成偶点
		if(find(x)==x)fa[x]=w;
		if(find(y)==y)fa[y]=w;
		x=pre[y];
	}
}
bool aug(int s){ // 从未匹配点 s 找增广路
	for(int i=1;i<=n;i++)fa[i]=i,vis[i]=pre[i]=0;
	while(!q.empty())q.pop();
	q.push(s);vis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int e=head[u];e;e=nxt[e]){
			int v=to[e];
			if(find(u)==find(v)||vis[v]==2)continue;
			if(!vis[v]){
				vis[v]=2;pre[v]=u;
				if(!mt[v]){ // 找到增广路, 沿 pre 翻转
					for(int x=v,y;x;x=y){
						y=mt[pre[x]];mt[x]=pre[x];mt[pre[x]]=x;
					}
					return true;
				}
				vis[mt[v]]=1;q.push(mt[v]);
			}else{ // u, v 都是偶点, 出现奇环
				int w=lca(u,v);
				blossom(u,v,w);blossom(v,u,w);
			}
		}
	}
	return false;
}
int solve(){
	int res=0;
	for(int i=1;i<=n;i++)if(!mt[i]&&aug(i))res++;
	return res;
}
