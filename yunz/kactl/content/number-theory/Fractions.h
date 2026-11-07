/**
 * Description: 分数 (有理数) 的精确运算. Frac 存分子 p 和分母 q, 总是约到最简且 $q > 0$, 0 存成 $0/1$.
 * mk(p, q) 用任意 $p$ 和 $q \neq 0$ 造一个约分后的分数; 支持 $+, -, \times, /$ (除数不能为 0) 和 $<, ==$.
 * 因为总是最简, 两个分数相等当且仅当 p, q 都相等. 比较大小用 \_\_int128 交叉相乘.
 * 溢出: 加减乘除会算 $p_1 q_2$ 这样的乘积, 要保证分子分母不超过约 $2 \cdot 10^9$;
 * 更大时把 ll 改成 \_\_int128 (gcd 要自己写, 输出时转回 ll).
 * Usage: Frac a = mk(1, 2), b = mk(1, 3);
 * Frac c = a + b; // c.p = 5, c.q = 6
 * Frac d = mk(4, -6); // d.p = -2, d.q = 3
 * if(d < a) ...; if(a == b) ...;
 * cout << c.p << '/' << c.q; // 输出 5/6
 * Time: 每次运算 O(\log)
 */
#pragma once

struct Frac{
	ll p,q; // p / q, q > 0, 已约分
};
Frac mk(ll p,ll q){ // q 不能为 0
	if(q<0){
		p=-p;
		q=-q;
	}
	ll g=gcd(p,q); // 非负, p = 0 时为 q
	return {p/g,q/g};
}
Frac operator+(Frac a,Frac b){
	return mk(a.p*b.q+b.p*a.q,a.q*b.q);
}
Frac operator-(Frac a,Frac b){
	return mk(a.p*b.q-b.p*a.q,a.q*b.q);
}
Frac operator*(Frac a,Frac b){return mk(a.p*b.p,a.q*b.q);}
Frac operator/(Frac a,Frac b){return mk(a.p*b.q,a.q*b.p);}
bool operator<(Frac a,Frac b){
	return (__int128)a.p*b.q<(__int128)b.p*a.q;
}
bool operator==(Frac a,Frac b){return a.p==b.p&&a.q==b.q;}
