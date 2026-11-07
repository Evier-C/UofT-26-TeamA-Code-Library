/**
 * Author: Simon Lindholm
 * Date: 2015-06-23
 * License: CC0
 * Source: own work
 * Description: 等差数列取模后的求和。
 *
 * \texttt{modsum(to, c, k, m)} = $\sum_{i=0}^{\mathrm{to}-1}{(ki+c) \% m}$。
 * \texttt{divsum} 类似，但求的是向下取整除法之和。
 * Usage: ll s = modsum(to, c, k, m); // 对 (k*i+c) mod m 求和
 * ull t = divsum(to, c, k, m); // 对 (k*i+c)/m 下取整求和
 * Time: $\log(m)$，常数较大。
 * Status: Tested for all |k|,|c|,to,m <= 50, and on kattis:aladin
 */
#pragma once

typedef unsigned long long ull;
ull sumsq(ull to){return to/2*((to-1)|1);}
/// ^ 写法特殊是为了正确处理溢出

ull divsum(ull to,ull c,ull k,ull m){
	ull res=k/m*sumsq(to)+c/m*to;
	k%=m;c%=m;
	if(!k)return res;
	ull to2=(to*k+c)/m;
	return res+(to-1)*to2-divsum(to2,m-1-c,m,k);
}

ll modsum(ull to,ll c,ll k,ll m){
	c=((c%m)+m)%m;
	k=((k%m)+m)%m;
	return to*c+k*sumsq(to)-m*divsum(to,c,k,m);
}
