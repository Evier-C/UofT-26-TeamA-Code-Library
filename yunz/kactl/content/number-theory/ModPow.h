/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description: 快速幂，计算 $b^e \bmod \texttt{mod}$。
 * Usage: ll r = modpow(b, e); // b 的 e 次方模 mod
 * Time: O(\log e)
 * Status: tested
 */
#pragma once

const ll mod=1000000007; // 设为 const 更快

ll modpow(ll b,ll e){
	ll ans=1;
	for(;e;b=b*b%mod,e/=2)
		if(e&1)ans=ans*b%mod;
	return ans;
}
