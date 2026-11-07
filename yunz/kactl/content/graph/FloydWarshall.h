/**
 * Description: Floyd 全源最短路 (点 $1..n$), 允许负边权.
 * 结束后 $d[i][j]$ 为最短距离, 不可达为 INF; 存在负环当且仅当
 * 某个 $d[i][i] < 0$. 最后一段把经过负环的点对标成 $-$INF (不需要可删).
 * Usage: init(n); d[u][v]=min(d[u][v],w); // 加边, 注意重边
 * floyd(n); if(d[u][v]==INF) 不可达; if(d[u][v]==-INF) 无下界
 * Time: O(n^3)
 */
#pragma once

const int N=505;
const ll INF=0x3f3f3f3f3f3f3f3fLL;
ll d[N][N];
void init(int n){
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
		d[i][j]=i==j?0:INF;
}
void floyd(int n){
	for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)if(d[i][k]<INF)
		for(int j=1;j<=n;j++)if(d[k][j]<INF)
			d[i][j]=min(d[i][j],max(d[i][k]+d[k][j],-INF));
	// 负环: 能经过负环的点对距离为 -INF
	for(int k=1;k<=n;k++)if(d[k][k]<0)
		for(int i=1;i<=n;i++)if(d[i][k]<INF)
			for(int j=1;j<=n;j++)if(d[k][j]<INF)d[i][j]=-INF;
}
