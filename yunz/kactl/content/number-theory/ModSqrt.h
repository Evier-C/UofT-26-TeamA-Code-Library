/**
 * Description: Cipolla 求二次剩余: 求 $x$ 使 $x^2 \equiv n \pmod p$, $p$ 为质数.
 * 找 $a$ 使 $w = a^2 - n$ 是非二次剩余, 则 $x = (a + \sqrt w)^{(p+1)/2}$,
 * 在 $\mathbb{F}_p[\sqrt w]$ 里算. 另一个解是 $p - x$. $p$ 可到 $10^{18}$.
 * Usage: ll x = cipolla(n, p); // 无解返回 -1, 有解返回较小的根
 * Time: 期望 O(\log p)
 */
#pragma once

typedef __int128 L;
ll pw(ll a,ll b,ll p){
	ll r=1%p;a%=p;
	for(;b;b>>=1,a=(L)a*a%p)if(b&1)r=(L)r*a%p;
	return r;
}
ll W; // w = a^2 - n
// (x + y sqrt w) 乘上 (a + b sqrt w)
void cmul(ll&x,ll&y,ll a,ll b,ll p){
	ll nx=((L)x*a+(L)y*b%p*W)%p;
	y=((L)x*b+(L)y*a)%p,x=nx;
}
ll cipolla(ll n,ll p){
	n%=p;if(n<0)n+=p;
	if(n==0||p==2)return n;
	if(pw(n,(p-1)/2,p)!=1)return -1; // 欧拉判别法
	ll a=0;
	do a++,W=((L)a*a%p-n+p)%p;
	while(pw(W,(p-1)/2,p)!=p-1);
	ll x=1,y=0,bx=a,by=1;
	for(ll e=(p+1)/2;e;e>>=1){
		if(e&1)cmul(x,y,bx,by,p);
		cmul(bx,by,bx,by,p);
	}
	return min(x,p-x);
}
