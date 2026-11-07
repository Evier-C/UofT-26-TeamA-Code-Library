/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: 求两个整数 $x$ 和 $y$，使 $ax+by=\gcd(a,b)$。若
 * 只需要 gcd，请直接用内置的 \texttt{\_\_gcd}。
 * 若 $a$ 与 $b$ 互质，则 $x$ 是 $a$ 的逆元 $\pmod{b}$。
 * Usage: ll x, y, g = euclid(a, b, x, y); // g = gcd(a, b)
 */
#pragma once

ll euclid(ll a,ll b,ll&x,ll&y){
	if(!b)return x=1,y=0,a;
	ll d=euclid(b,a%b,y,x);
	return y-=a/b*x,d;
}
