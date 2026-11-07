/**
 * Author: Unknown
 * Date: 2014-11-27
 * Source: somewhere on github
 * Description: 在模 \texttt{mod} 意义下计算整数矩阵的行列式 (辗转相除消元, 模数不必为素数).
 * 去掉取模即得纯整数版本. 会破坏原矩阵.
 * Usage: vector<vector<ll>> a(n, vector<ll>(n));
 * ll d = det(a); // a 会被修改
 * Time: $O(N^3)$
 * Status: bruteforce-tested for N <= 3, mod <= 7
 */
#pragma once

const ll mod = 12345;
ll det(vector<vector<ll>>& a) {
	int n = sz(a); ll ans = 1;
	rep(i,0,n) {
		rep(j,i+1,n) {
			while (a[j][i] != 0) { // 辗转相除
				ll t = a[i][i] / a[j][i];
				if (t) rep(k,i,n)
					a[i][k] = (a[i][k] - a[j][k] * t) % mod;
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		ans = ans * a[i][i] % mod;
		if (!ans) return 0;
	}
	return (ans + mod) % mod;
}
