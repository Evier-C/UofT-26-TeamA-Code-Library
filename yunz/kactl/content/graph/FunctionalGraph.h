/**
 * Description: 基环树森林 / 内向树 (函数图): 每个点 $i$ 恰有一条出边
 * 指向 $a[i]$, 点 $1..n$, $1 \le a[i] \le n$. 每个连通块恰有一个环,
 * 其余点形成挂在环上的树. solve(n) 非递归, 求出:
 * cyc[1..cnt]: 每个环上的点, 按出边顺序 (cyc[k][j] 的下一个点是
 * cyc[k][(j+1)\%len], len 为环长 cyc[k].size()).
 * rt[u]: 从 $u$ 出发第一个到达的环上点 (环上点为自己);
 * dep[u]: $u$ 到 rt[u] 的步数 (尾巴长度, 环上点为 0);
 * bel[u]: 所在环的编号; pos[u]: rt[u] 在 cyc[bel[u]] 中的下标.
 * 从 $u$ 走 $k$ 步 ($k \ge$ dep[u]) 到达
 * cyc[bel[u]][(pos[u]+k-dep[u])\%len]; $k <$ dep[u] 时要用倍增.
 * Usage: for(int i=1;i<=n;i++) cin>>a[i];
 * solve(n); // 多组数据直接重新调用
 * bool onCycle=(dep[u]==0);
 * int len=cyc[bel[u]].size(); // u 所在环的长度
 * Time: O(n)
 */
#pragma once

const int N=2e5+5;
int a[N],vis[N],rt[N],dep[N],bel[N],pos[N],cnt;
int st[N],tp; // 当前路径上的点
vector<int>cyc[N];
void solve(int n){
	cnt=0;
	for(int i=1;i<=n;i++)vis[i]=0;
	// vis: 0 未访问, 1 在当前路径上, 2 已处理完
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		int u=i;
		tp=0;
		while(!vis[u]){
			vis[u]=1;
			st[++tp]=u;
			u=a[u];
		}
		if(vis[u]==1){ // 找到新环, u 在环上
			cyc[++cnt].clear();
			while(vis[u]==1){
				vis[u]=2;
				rt[u]=u;
				dep[u]=0;
				bel[u]=cnt;
				pos[u]=cyc[cnt].size();
				cyc[cnt].push_back(u);
				u=a[u];
			}
		}
		// 倒着处理路径上不在环上的点
		for(;tp;tp--){
			int v=st[tp];
			if(vis[v]==2)continue;
			vis[v]=2;
			rt[v]=rt[a[v]];
			dep[v]=dep[a[v]]+1;
			bel[v]=bel[a[v]];
			pos[v]=pos[a[v]];
		}
	}
}
