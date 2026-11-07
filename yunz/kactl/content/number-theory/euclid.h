/**
 * Description: 扩展欧几里得, 求 $x, y$ 使 $ax + by = \gcd(a, b)$, 返回 $\gcd$.
 * 结果满足 $|x| \le |b|, |y| \le |a|$. 只要 gcd 用 \_\_gcd(a, b).
 * $a, m$ 互质时 $x$ 就是 $a$ 模 $m$ 的逆元 (调用 exgcd(a, m, x, y)).
 * 解 $ax + by = c$: 有解当且仅当 $g | c$, 一组解为 $x \cdot c/g$;
 * 通解 $x + k \cdot b/g$, 最小非负 $x$ 对 $b/g$ 取模.
 * Usage: ll x, y, g = exgcd(a, b, x, y);
 * ll iv = (x \% m + m) \% m; // exgcd(a, m, x, y) 后, a 的逆元
 * Time: O(\log \min(a, b))
 */
#pragma once

ll exgcd(ll a,ll b,ll&x,ll&y){
	if(!b){x=1,y=0;return a;}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
