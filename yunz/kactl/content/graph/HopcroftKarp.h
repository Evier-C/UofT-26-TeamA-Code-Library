/**
 * Description: 二分图最大匹配 Hopcroft-Karp.
 * 输入: 左部点 $1..n$, 右部点 $1..m$ (左右各自编号, 可以重号),
 * 先 init(n,m), 再对每条边 g[u].push\_back(v) (左 $u$ 连右 $v$).
 * 函数: hk() 返回最大匹配数. 结果: mL[u] 为左部点 $u$ 匹配的右部点,
 * mR[v] 为右部点 $v$ 匹配的左部点, 未匹配为 0.
 * 做法: 每轮 bfs 从左部未匹配点出发给左部点分层 (d[u]),
 * 再 dfs 沿层找一批不相交的最短增广路; 共 $O(\sqrt{V})$ 轮.
 * 注意: N 为左右部点数的上限. dfs 递归深度可达 $n$.
 * 与其他用全局变量 n, m, N 的模板不能同时 include
 * (MinimumVertexCover.h 已经 include 本文件).
 * Usage: init(n,m); // 每组数据先调用
 * for(int i=1;i<=k;i++){
 *   cin>>u>>v; // 左 u, 右 v
 *   g[u].push_back(v);
 * }
 * cout<<hk()<<endl; // 最大匹配数
 * for(int u=1;u<=n;u++) // 输出匹配边
 *   if(mL[u]) cout<<u<<' '<<mL[u]<<endl;
 * Time: O(E \sqrt{V})
 */
#pragma once

const int N=1e5+5; // 左右部点数的最大值
int n,m,mL[N],mR[N],d[N];
vector<int>g[N];
void init(int _n,int _m){
	n=_n;
	m=_m;
	for(int i=1;i<=n;i++)g[i].clear();
}
bool dfs(int u){
	int t=d[u]+1;
	d[u]=0; // 本轮不再访问 u
	for(int v:g[u]){
		if(!mR[v]||(d[mR[v]]==t&&dfs(mR[v]))){
			mL[u]=v;
			mR[v]=u;
			return true;
		}
	}
	return false;
}
int hk(){
	for(int i=1;i<=n;i++)mL[i]=0;
	for(int i=1;i<=m;i++)mR[i]=0;
	int res=0;
	while(true){
		// d[u] 为左部点 u 的层数, 0 表示不可用
		queue<int>q;
		bool found=false;
		for(int i=1;i<=n;i++){
			d[i]=0;
			if(!mL[i]){
				d[i]=1;
				q.push(i);
			}
		}
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int v:g[u]){
				int w=mR[v];
				if(!w){
					found=true;
				}else if(!d[w]){
					d[w]=d[u]+1;
					q.push(w);
				}
			}
		}
		if(!found)return res;
		for(int i=1;i<=n;i++){
			if(!mL[i]&&dfs(i))res++;
		}
	}
}
