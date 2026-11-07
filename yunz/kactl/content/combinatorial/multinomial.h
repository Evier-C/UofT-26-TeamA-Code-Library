/**
 * Description: 计算多项式系数 $\displaystyle \binom{k_1 + \dots + k_n}{k_1, k_2, \dots, k_n} = \frac{(\sum k_i)!}{k_1!k_2!...k_n!}$,
 * 即把 $k_1$ 个 1 号球, $k_2$ 个 2 号球, ... 排成一排的方案数.
 * 输入 vector k, 每个 $k_i \ge 0$, 空的 vector 返回 1. 不取模, 精确计算:
 * 逐个乘组合数, 每步都能整除. 要求结果乘上 $\sum k_i$ 不超过 ll,
 * 否则中间值溢出. 要取模就改用阶乘和逆元.
 * Usage: vector<int> k = {2, 1, 1};
 * ll c = multinomial(k); // 4! / (2! 1! 1!) = 12
 * Time: $O(\sum k_i)$
 */
#pragma once

ll multinomial(const vector<int>&k){
	ll c=1;
	int m=0; // m: 已放入的个数
	for(int x:k){
		for(int j=1;j<=x;j++){
			m++;
			c=c*m/j;
		}
	}
	return c;
}
