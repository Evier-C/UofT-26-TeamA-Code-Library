/**
 * Author: Lucian Bicsi, Simon Lindholm
 * Date: 2017-10-31
 * License: CC0
 * Description: 给定 $f$ 和 $N$，求使 $f(p/q)$ 为真的最小分数 $p/q \in [0, 1]$，
 * 其中 $p, q \le N$。
 * 若 $f$ 找到精确解，可以在 $f$ 中抛出异常，
 * 此时可以去掉 $N$ 的限制。
 * Usage: Frac r = fracBS([](Frac f) { return 3*f.p >= f.q; }, 10);
 * // r = {1, 3}, 即 1/3
 * Time: O(\log(N))
 * Status: stress-tested for n <= 300
 */

struct Frac { ll p, q; };

template<class F>
Frac fracBS(F f, ll N) {
	bool dir = 1, A = 1, B = 1;
	Frac lo{0, 1}, hi{1, 1}; // 把 hi 设为 1/0 可搜索 (0, N]
	if (f(lo)) return lo;
	assert(f(hi));
	while (A || B) {
		ll adv = 0, step = 1; // dir 为真移动 hi, 否则移动 lo
		for (int si = 0; step; (step *= 2) >>= si) {
			adv += step;
			Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
			if (abs(mid.p) > N || mid.q > N || dir == !f(mid)) {
				adv -= step; si = 2;
			}
		}
		hi.p += lo.p * adv;
		hi.q += lo.q * adv;
		dir = !dir;
		swap(lo, hi);
		A = B; B = !!adv;
	}
	return dir ? hi : lo;
}
