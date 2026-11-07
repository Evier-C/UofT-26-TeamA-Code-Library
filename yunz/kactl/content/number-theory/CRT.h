/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: 中国剩余定理。
 *
 * \texttt{crt(a, m, b, n)} 求 $x$ 使 $x\equiv a \pmod m$，$x\equiv b \pmod n$。
 * 若 $|a| < m$ 且 $|b| < n$，则 $x$ 满足 $0 \le x < \text{lcm}(m, n)$。
 * 要求 $mn < 2^{62}$。
 * Usage: ll x = crt(a, m, b, n); // 无解时 assert 失败
 * Time: $\log(n)$
 * Status: Works
 */
#pragma once

#include "euclid.h"

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	assert((a - b) % g == 0); // 否则无解
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}
