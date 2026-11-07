/**
 * Description: 基环树森林 / 内向树: 每个点 $i$ 恰有一条出边指向 $a[i]$
 * ($1 \le a[i] \le n$). cyc[1..cnt] 为各个环 (沿出边的顺序,
 * cyc[k][j] 的下一个点为 cyc[k][(j+1)\%len]). 对每个点 $u$: rt[u] 为
 * 从 $u$ 出发第一个到达的环上点, dep[u] 为到 rt[u] 的步数 (尾巴长度,
 * 环上点为 0), bel[u] 为所在环编号, pos[u] 为 rt[u] 在环中的下标.
 * 从 $u$ 走 $k \ge$ dep[u] 步到达 cyc[bel[u]][(pos[u]+k-dep[u])\%len].
 * Usage: for(int i=1;i<=n;i++) cin>>a[i];
 * solve(n); // 多组数据直接重新调用
 * bool onCycle=(dep[u]==0); int len=cyc[bel[u]].size();
 * Time: O(n)
 */
#pragma once

const int N=2e5+5;
int a[N],vis[N],rt[N],dep[N],bel[N],pos[N],cnt,st[N],tp;
vector<int>cyc[N];
void solve(int n){
	cnt=0;
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=n;i++)if(!vis[i]){
		int u=i;tp=0;
		while(!vis[u])vis[u]=1,st[++tp]=u,u=a[u];
		if(vis[u]==1){ // 找到新环, u 在环上
			cyc[++cnt].clear();
			while(vis[u]==1){
				vis[u]=2,rt[u]=u,dep[u]=0,bel[u]=cnt;
				pos[u]=cyc[cnt].size(),cyc[cnt].push_back(u);
				u=a[u];
			}
		}
		// 倒着处理链上的点
		for(;tp;tp--){
			int v=st[tp];
			if(vis[v]==2)continue;
			vis[v]=2,rt[v]=rt[a[v]],dep[v]=dep[a[v]]+1;
			bel[v]=bel[a[v]],pos[v]=pos[a[v]];
		}
	}
}
