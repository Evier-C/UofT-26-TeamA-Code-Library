/**
 * Author: Lucian Bicsi
 * Date: 2018-02-14
 * License: CC0
 * Source: Chinese material
 * Description: 给定 $S[0 \ldots \ge n-1]$ 与 $tr[0 \ldots n-1]$, 求 $n$ 阶
 * 线性递推 $S[i] = \sum_j S[i-j-1]tr[j]$ 的第 $k$ 项 ($k$ 从 0 开始, 模 \texttt{mod}).
 * 比矩阵快速幂更快.
 * 常与 Berlekamp--Massey 配合使用.
 * Usage: linearRec({0, 1}, {1, 1}, k) // 第 k 个 Fibonacci 数
 * Time: O(n^2 \log k)
 * Status: bruteforce-tested mod 5 for n <= 5
 */
#pragma once

const ll mod = 5; /** exclude-line */

typedef vector<ll> Poly;
ll linearRec(Poly S, Poly tr, ll k) {
	int n = sz(tr);
	if (n == 0) return S[0];

	auto combine = [&](Poly a, Poly b) {
		Poly res(n * 2 + 1);
		rep(i,0,n+1) rep(j,0,n+1)
			res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
		for (int i = 2 * n; i > n; --i) rep(j,0,n)
			res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % mod;
		res.resize(n + 1);
		return res;
	};

	Poly pol(n + 1), e(pol);
	pol[0] = e[1] = 1;

	for (++k; k; k /= 2) {
		if (k % 2) pol = combine(pol, e);
		e = combine(e, e);
	}

	ll res = 0;
	rep(i,0,n) res = (res + pol[i + 1] * S[i]) % mod;
	return res;
}
