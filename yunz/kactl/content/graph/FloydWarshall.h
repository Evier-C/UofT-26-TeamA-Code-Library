/**
 * Description: Floyd 全源最短路, 点 $1..n$, 有向图, 允许负边权.
 * init(n): 令 $d[i][i]=0$, 其余为 INF. 加边时 d[u][v] 取 min (处理重边;
 * 无向图两个方向都加). floyd(n) 之后 $d[i][j]$ 为 $i$ 到 $j$ 的最短距离,
 * 不可达为 INF. 存在负环当且仅当某个 $d[i][i] < 0$; 最后一段把能
 * 经过负环的点对标成 $-$INF (不需要可删). 距离为 ll, 中间结果截断在
 * $-$INF, 不会溢出. N 为点数上限 (约 500).
 * Usage: init(n); // 多组数据每组调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v>>w;
 *   d[u][v]=min(d[u][v],w);
 * }
 * floyd(n);
 * // d[u][v]==INF 不可达, d[u][v]==-INF 无下界
 * Time: O(n^3)
 */
#pragma once

const int N=505;
const ll INF=0x3f3f3f3f3f3f3f3fLL;
ll d[N][N];
void init(int n){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)d[i][j]=i==j?0:INF;
	}
}
void floyd(int n){
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			if(d[i][k]==INF)continue;
			for(int j=1;j<=n;j++){
				if(d[k][j]==INF)continue;
				d[i][j]=min(d[i][j],max(d[i][k]+d[k][j],-INF));
			}
		}
	}
	// 负环: 能经过负环的点对距离为 -INF
	for(int k=1;k<=n;k++){
		if(d[k][k]>=0)continue;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(d[i][k]<INF&&d[k][j]<INF)d[i][j]=-INF;
			}
		}
	}
}
