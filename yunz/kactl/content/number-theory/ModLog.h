/**
 * Description: 离散对数 (BSGS): 返回最小的 $x \ge 0$, 无解返回 $-1$. $b \equiv 1$ 时答案为 0.
 * 输入非负. $m$ 不超过约 $10^9$, 否则乘法要改 \_\_int128.
 * Usage: ll x = bsgs(3, 13, 17); // 3^x = 13 (mod 17), gcd(a, m) = 1
 * ll y = bsgs(a, b, m, c); // c * a^x = b, gcd(a, m) = 1
 * ll z = exbsgs(a, b, m); // a^x = b (mod m), a, m 任意
 * // a 的阶, 即最小的 k 使 a^k = 1, 为 bsgs(a, 1, m, a) + 1
 * Time: O(\sqrt m)
 */
#pragma once

ll bsgs(ll a,ll b,ll m,ll c=1){
	a%=m;
	b%=m;
	c%=m;
	if(c==b)return 0;
	ll t=sqrtl(m)+1;
	ll at=1; // a^t
	unordered_map<ll,ll>h; // b * a^j 对应的最大的 j
	ll cur=b;
	for(ll j=0;j<t;j++){
		h[cur]=j;
		cur=cur*a%m;
		at=at*a%m;
	}
	// 找 c * a^(i t) = b * a^j, 则 x = i t - j
	cur=c;
	for(ll i=1;i<=t;i++){
		cur=cur*at%m;
		if(h.count(cur))return i*t-h[cur];
	}
	return -1;
}
ll exbsgs(ll a,ll b,ll m){
	a%=m;
	b%=m;
	if(b==1%m)return 0;
	ll k=0,c=1;
	while(true){
		ll d=__gcd(a,m);
		if(d==1)break;
		if(b%d)return -1;
		b/=d;
		m/=d;
		k++;
		c=c*(a/d)%m;
		if(c==b)return k; // x = k
	}
	ll x=bsgs(a,b,m,c);
	if(x<0)return -1;
	return x+k;
}
