/**
 * Author: chilli, c1729, Simon Lindholm
 * Date: 2019-03-28
 * License: CC0
 * Source: Wikipedia, https://miller-rabin.appspot.com/
 * Description: 确定性 Miller-Rabin 素性测试。
 * 保证对不超过 $7 \cdot 10^{18}$ 的数正确；更大的数请用 Python，并随机扩充 A。
 * Usage: bool p = isPrime(n); // n 为 ull
 * Time: $a^b \mod c$ 复杂度的 7 倍。
 * Status: Stress-tested
 */
#pragma once

#include "ModMulLL.h"

bool isPrime(ull n){
	if(n<2||n%6%4!=1)return (n|1)==3;
	ull A[]={2,325,9375,28178,450775,9780504,1795265022},
	    s=__builtin_ctzll(n-1),d=n>>s;
	for(ull a:A){ // ^ 末尾 0 的个数
		ull p=modpow(a%n,d,n),i=s;
		while(p!=1&&p!=n-1&&a%n&&i--)
			p=modmul(p,p,n);
		if(p!=n-1&&i!=s)return 0;
	}
	return 1;
}
