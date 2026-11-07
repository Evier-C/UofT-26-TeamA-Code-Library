/**
 * Description: 计算多项式系数 $\displaystyle \binom{k_1 + \dots + k_n}{k_1, k_2, \dots, k_n} = \frac{(\sum k_i)!}{k_1!k_2!...k_n!}$.
 * 逐个乘组合数, 每步都整除, 不取模; 结果和中间值 c * m 都要不超过 ll.
 * Usage: ll c = multinomial({2, 1, 1}); // 4! / (2! 1! 1!) = 12
 * Time: $O(\sum k_i)$
 */
#pragma once

ll multinomial(const vector<int>&k){
	ll c=1;int m=0; // m: 已放入的个数
	for(int x:k)
		for(int j=1;j<=x;j++)c=c*++m/j;
	return c;
}
