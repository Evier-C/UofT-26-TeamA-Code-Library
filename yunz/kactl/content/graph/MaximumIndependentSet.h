/**
 * Author: chilli
 * Date: 2019-05-17
 * Source: Wikipedia
 * Description: 求一般图的最大独立集: 对补图求最大团 (见 MaximumClique).
 * 若图是二分图, 见 MinimumVertexCover.
 * Usage: vb h(n); // 补图
 * rep(i,0,n) rep(j,0,n) h[i][j] = i != j \&\& !g[i][j];
 * vi s = Maxclique(h).maxClique(); // 即最大独立集
 */
