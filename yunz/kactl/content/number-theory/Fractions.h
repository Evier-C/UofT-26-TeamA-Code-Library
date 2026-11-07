/**
 * Description: 分数, 分子分母为 long long, 总是约分且分母为正.
 * 运算中 $p \cdot q$ 可能溢出: 保证分子分母不超过约 $10^9$,
 * 或者把 ll 改成 \_\_int128 (输出时转回 ll).
 * Usage: Frac a = mk(1, 2), b = mk(1, 3); Frac c = a + b; // 5/6
 * c.p, c.q 为分子分母; a < b, a == b 可直接比较
 * Time: 每次运算 O(\log)
 */
#pragma once

struct Frac{ll p,q;};
Frac mk(ll p,ll q){ // q 不能为 0
	if(q<0)p=-p,q=-q;
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
