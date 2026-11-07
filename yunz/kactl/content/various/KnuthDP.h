/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: 区间 DP $a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$ 中，若（最小的）最优 $k$ 随 $i$ 和 $j$ 都单调不减，
 *  则可按区间长度递增的顺序求解，且求 $a[i][j]$ 时只需在 $p[i][j-1]$ 与 $p[i+1][j]$ 之间搜索 $k = p[i][j]$。
 *  这称为 Knuth DP。充分条件为：对所有 $a \le b \le c \le d$，有 $f(b,c) \le f(a,d)$ 且 $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$。
 *  另可考虑：LineContainer（数据结构一章）、单调队列、三分搜索。
 * Usage: rep(len,2,n+1) rep(i,0,n-len+1) { int j = i+len;
 *  rep(k, max(i+1, p[i][j-1]), min(j-1, p[i+1][j]) + 1)
 *   用 k 更新 a[i][j] 和 p[i][j]; } // 初始 p[i][i+1] = i
 * Time: O(N^2)
 */
