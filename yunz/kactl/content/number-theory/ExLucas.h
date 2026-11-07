/**
 * Description: 扩展 Lucas, $P$ 不必是质数. $n, m, P \le 10^{18}$, 但 $P$ 的每个质数幂因子 $p^k$ 要在约 $10^6$ 以内.
 * 自带 pw, 不依赖其他文件.
 * Usage: ll c = exlucas(n, m, P); // C(n, m) mod P
 * ll d = exlucas(10, 3, 1000); // 120
 * // m < 0 或 m > n 时返回 0
 * Time: O(\sum p^k \log n)
 */
#pragma once

ll pw(ll b,ll e,ll m){
	ll r=1%m;
	b%=m;
	while(e){
		if(e&1)r=r*b%m;
		b=b*b%m;
		e>>=1;
	}
	return r;
}
// n! 去掉所有因子 p 后模 pk
ll facp(ll n,ll p,ll pk){
	if(n==0)return 1;
	ll r=1;
	for(ll i=1;i<=pk;i++){
		if(i%p)r=r*i%pk;
	}
	r=pw(r,n/pk,pk);
	for(ll i=1;i<=n%pk;i++){
		if(i%p)r=r*i%pk;
	}
	return r*facp(n/p,p,pk)%pk;
}
// C(n, m) mod pk, pk = p^k
ll Cpk(ll n,ll m,ll p,ll pk){
	ll e=0; // C(n, m) 中因子 p 的次数
	for(ll t=n;t;t/=p)e+=t/p;
	for(ll t=m;t;t/=p)e-=t/p;
	for(ll t=n-m;t;t/=p)e-=t/p;
	ll ph=pk/p*(p-1); // phi(pk)
	ll r=facp(n,p,pk);
	r=r*pw(facp(m,p,pk),ph-1,pk)%pk;
	r=r*pw(facp(n-m,p,pk),ph-1,pk)%pk;
	return r*pw(p,e,pk)%pk;
}
ll exlucas(ll n,ll m,ll P){
	if(m<0||m>n)return 0;
	ll x=0,M=1; // 已合并的解 x mod M
	ll Q=P;
	for(ll p=2;Q>1;p++){
		if(p*p>Q)p=Q;
		if(Q%p)continue;
		ll pk=1;
		while(Q%p==0){
			Q/=p;
			pk*=p;
		}
		ll r=Cpk(n,m,p,pk);
		ll ph=pk/p*(p-1);
		// 求 t 使 x + M t = r (mod pk), M 与 pk 互质
		ll t=(r-x%pk+pk)%pk*pw(M,ph-1,pk)%pk;
		x+=M*t;
		M*=pk;
	}
	return x;
}
