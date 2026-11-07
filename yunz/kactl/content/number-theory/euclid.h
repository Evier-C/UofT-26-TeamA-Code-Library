/**
 * Description: 扩展欧几里得. exgcd(a, b, x, y) 求一组整数 $x, y$ 使 $ax + by = \gcd(a, b)$, 返回 $g = \gcd(a, b)$.
 * 要求 $a, b \ge 0$ 且不全为 0. 得到的解满足 $|x| \le b$, $|y| \le a$, 中间不会溢出.
 * 只要 gcd 时直接用 \_\_gcd(a, b).
 * 求逆元: $\gcd(a, m) = 1$ 时 exgcd(a, m, x, y) 的 $x$ 就是 $a$ 模 $m$ 的逆元 (调成 $[0, m)$), $m$ 不必是质数.
 * 解 $ax + by = c$: 有解当且仅当 $g$ 整除 $c$; 一组解为 $x_0 = x \cdot c/g$, $y_0 = y \cdot c/g$ (注意溢出, 可用 \_\_int128);
 * 通解 $x = x_0 + k \cdot b/g$, $y = y_0 - k \cdot a/g$; 最小非负 $x$ 为 $x_0$ 对 $b/g$ 取模.
 * Usage: ll x, y;
 * ll g = exgcd(a, b, x, y); // a * x + b * y = g
 * exgcd(a, m, x, y); // a, m 互质
 * ll iv = (x \% m + m) \% m; // a 模 m 的逆元
 * Time: O(\log \min(a, b))
 */
#pragma once

ll exgcd(ll a,ll b,ll&x,ll&y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
