/**
 * Description: 带权二分图最优匹配 (KM / 匈牙利算法, 势能 + Dijkstra 式).
 * 左部 $1..n$, 右部 $1..m$, 要求 $n \le m$ (否则转置). a[i][j] 为左 $i$
 * 匹配右 $j$ 的代价, 给每个左部点匹配不同的右部点, 使代价和最小.
 * 返回最小代价, 左 $i$ 匹配右 ans[i]. 没有的边设为很大的代价 (如 $10^{12}$).
 * 最大权: 代价取负, 答案再取负. 最大权且允许不匹配:
 * 代价设为 $-\max(w,0)$, 并补 0 让 $n = m$.
 * Usage: n=..., m=...; a[i][j]=w; // 1-indexed, 多组数据直接覆盖 a
 * ll c=km(); // 左 i 匹配右 ans[i]
 * // 最大权完美匹配: a[i][j]=-w[i][j]; ll best=-km();
 * Time: O(n^2 m)
 */
#pragma once

const int N=505; // n, m 的最大值
const ll INF=1e18; // 大于任意可能的代价和
int n,m,p[N],way[N],ans[N]; // p[j]: 右 j 匹配的左部点
ll a[N][N],u[N],v[N],minv[N];
bool used[N];
ll km(){
	for(int i=0;i<=n;i++)u[i]=0;
	for(int j=0;j<=m;j++)v[j]=0,p[j]=0;
	for(int i=1;i<=n;i++){
		p[0]=i;int j0=0; // 虚拟右部点 0
		for(int j=0;j<=m;j++)minv[j]=INF,used[j]=0;
		do{ // 找一条到未匹配右部点的最短增广路
			used[j0]=1;
			int i0=p[j0],j1=0;ll delta=INF;
			for(int j=1;j<=m;j++)if(!used[j]){
				ll cur=a[i0][j]-u[i0]-v[j];
				if(cur<minv[j])minv[j]=cur,way[j]=j0;
				if(minv[j]<delta)delta=minv[j],j1=j;
			}
			for(int j=0;j<=m;j++)
				if(used[j])u[p[j]]+=delta,v[j]-=delta;
				else minv[j]-=delta;
			j0=j1;
		}while(p[j0]);
		// 沿增广路翻转
		do{int j1=way[j0];p[j0]=p[j1];j0=j1;}while(j0);
	}
	for(int j=1;j<=m;j++)if(p[j])ans[p[j]]=j;
	return -v[0];
}
