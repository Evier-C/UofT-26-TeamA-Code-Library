/**
 * Description: 二次剩余 (Cipolla 算法): 求 $x$ 使 $x^2 \equiv n \pmod p$, $p$ 必须是质数.
 * cipolla(n, p) 无解时返回 $-1$; 有解时返回两个根 $x, p - x$ 中较小的那个 ($n \equiv 0$ 时返回 0).
 * $n$ 可以为负或大于 $p$. 判断有无解用欧拉判别法: $n^{(p-1)/2} \equiv 1$ 才有解.
 * 做法: 找 $a$ 使 $w = a^2 - n$ 不是二次剩余, 在 $\mathbb{F}_p[\sqrt w]$ 里算 $x = (a + \sqrt w)^{(p+1)/2}$.
 * cmul 是这个域里的乘法, $(x + y\sqrt w)(a + b\sqrt w)$. 全部乘法用 \_\_int128, $p$ 可到 $10^{18}$.
 * Usage: ll x = cipolla(2, 7); // 3, 因为 3 * 3 = 9 = 2 (mod 7)
 * if(x == -1) ... // 无解
 * else { ll y = p - x; } // 另一个根 (x = 0 时只有一个根)
 * Time: 期望 O(\log p)
 */
#pragma once

typedef __int128 L;
ll pw(ll a,ll b,ll p){
	ll r=1%p;
	a%=p;
	while(b){
		if(b&1)r=(L)r*a%p;
		a=(L)a*a%p;
		b>>=1;
	}
	return r;
}
ll W; // w = a^2 - n
// (x + y sqrt w) 乘上 (a + b sqrt w), 结果存回 x, y
void cmul(ll&x,ll&y,ll a,ll b,ll p){
	ll nx=((L)x*a+(L)y*b%p*W)%p;
	ll ny=((L)x*b+(L)y*a)%p;
	x=nx;
	y=ny;
}
ll cipolla(ll n,ll p){
	n%=p;
	if(n<0)n+=p;
	if(n==0||p==2)return n;
	if(pw(n,(p-1)/2,p)!=1)return -1; // 欧拉判别法
	ll a=0;
	while(true){
		a++;
		W=((L)a*a%p-n+p)%p;
		if(pw(W,(p-1)/2,p)==p-1)break;
	}
	ll x=1,y=0;
	ll bx=a,by=1;
	for(ll e=(p+1)/2;e;e>>=1){
		if(e&1)cmul(x,y,bx,by,p);
		cmul(bx,by,bx,by,p);
	}
	return min(x,p-x);
}
