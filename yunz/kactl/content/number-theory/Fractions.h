/**
 * Description: 分数, 总是最简且分母为正. 分子分母要不超过约 $2 \cdot 10^9$, 否则乘法溢出 (可改 \_\_int128).
 * Usage: Frac a = mk(1, 2), b = mk(1, 3); // 分母不能为 0
 * Frac c = a + b; // c.p = 5, c.q = 6; 还有 - * /
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
