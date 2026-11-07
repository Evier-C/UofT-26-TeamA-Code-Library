/**
 * Description: Floyd 全源最短路, 有向图, 允许负边权. 点数 N 约 500.
 * 有负环当且仅当某个 d[i][i] $< 0$. 对象必须是全局变量.
 * Usage: FW.init(n); // 多组数据每组调用
 * for(int i=1;i<=m;i++){
 *   cin>>u>>v>>w;
 *   FW.d[u][v]=min(FW.d[u][v],w); // 重边取 min, 无向图加两次
 * }
 * FW.floyd(n);
 * ll x=FW.d[u][v]; // u 到 v 的最短距离
 * // x==FW.INF 不可达; x==-FW.INF 经过负环, 无下界
 * Floyd FW2; // 第二个对象 (全局)
 * Time: O(n^3)
 */
#pragma once

struct Floyd{
	static const int N=505;
	static constexpr ll INF=0x3f3f3f3f3f3f3f3fLL;
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
}FW;
