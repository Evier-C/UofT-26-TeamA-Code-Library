/**
 * Author: Simon Lindholm
 * Date: 2018-07-15
 * License: CC0
 * Source: Wikipedia
 * Description: 给定 $N$ 和实数 $x \ge 0$，求满足 $p, q \le N$ 的最接近 $x$ 的有理数 $p/q$。
 * 结果满足 $|p/q - x| \le 1/qN$。
 *
 * 相邻的渐近分数满足 $p_{k+1}q_k - q_{k+1}p_k = (-1)^k$。
 * （$p_k/q_k$ 交替地 $>x$ 与 $<x$。）
 * 若 $x$ 为有理数，$y$ 最终变为 $\infty$；
 * 若 $x$ 是 $2$ 次多项式的根，则 $a$ 序列最终循环。
 * Usage: auto [p, q] = approximate(x, N); // pair<ll, ll>
 * Time: O(\log N)
 * Status: stress-tested for n <= 300
 */

typedef double d; // N 约 1e7 时可用 ; N 约 1e9 用 long double
pair<ll, ll> approximate(d x, ll N) {
	ll LP = 0, LQ = 1, P = 1, Q = 0, inf = LLONG_MAX; d y = x;
	for (;;) {
		ll lim = min(P ? (N-LP) / P : inf, Q ? (N-LQ) / Q : inf),
		   a = (ll)floor(y), b = min(a, lim),
		   NP = b*P + LP, NQ = b*Q + LQ;
		if (a > b) {
			// 若 b 大于 a/2, 存在更优的半渐近分数
			// 若 b = a/2, 则可能存在
			// 可在此直接返回 {P, Q} 以得到更规范的逼近
			return (abs(x - (d)NP / (d)NQ) < abs(x - (d)P / (d)Q)) ?
				make_pair(NP, NQ) : make_pair(P, Q);
		}
		if (abs(y = 1/(y - (d)a)) > 3*N) {
			return {NP, NQ};
		}
		LP = P; P = NP;
		LQ = Q; Q = NQ;
	}
}
