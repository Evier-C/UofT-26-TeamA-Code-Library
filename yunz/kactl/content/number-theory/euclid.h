/**
 * Description: 扩展欧几里得. 要求 $a, b \ge 0$ 且不全为 0, 解满足 $|x| \le b$, $|y| \le a$.
 * $ax + by = c$ 有解当且仅当 $g$ 整除 $c$.
 * Usage: ll x, y;
 * ll g = exgcd(a, b, x, y); // a * x + b * y = g = gcd(a, b)
 * exgcd(a, m, x, y); // a, m 互质, m 不必是质数
 * ll iv = (x \% m + m) \% m; // a 模 m 的逆元
 * // a x + b y = c 的一组解: x * (c / g), 注意溢出
 * // 通解 x + k * (b / g), 最小非负 x 对 b / g 取模
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
