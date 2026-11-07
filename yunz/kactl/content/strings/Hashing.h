/**
 * Description: 字符串哈希, 双模数. 串 s[1..n] 为 1-indexed.
 * 两个模数的结果合成一个 ll 返回, 可直接比较或放进 map/set.
 * 双模冲突概率约 $10^{-18}$, 很安全. 单模 $10^9+7$ 在比较约 $10^5$ 个串时
 * 就可能因生日悖论冲突; 自然溢出 (unsigned long long) 最快,
 * 但会被 Thue-Morse 串卡掉. 怕被 hack 时可把 B1, B2 换成随机数.
 * Usage: build(s,n); // 预处理 s 的前缀哈希
 * ll x=get(l,r); // s[l..r] 的哈希
 * ll y=calc(t,m); // 整个 t[1..m] 的哈希, 可与 get 比较
 * Time: 预处理 O(n), 查询 O(1)
 */
#pragma once

const int N=1e6+5; // 串长上限
const int M1=1e9+7,M2=998244353,B1=131,B2=13331;
int h1[N],h2[N],p1[N],p2[N];
void build(char*s,int n){
	p1[0]=p2[0]=1;h1[0]=h2[0]=0;
	for(int i=1;i<=n;i++){
		p1[i]=1ll*p1[i-1]*B1%M1;
		p2[i]=1ll*p2[i-1]*B2%M2;
		h1[i]=(1ll*h1[i-1]*B1+s[i])%M1;
		h2[i]=(1ll*h2[i-1]*B2+s[i])%M2;
	}
}
ll get(int l,int r){
	ll x=(h1[r]-1ll*h1[l-1]*p1[r-l+1]%M1+M1)%M1;
	ll y=(h2[r]-1ll*h2[l-1]*p2[r-l+1]%M2+M2)%M2;
	return x*M2+y;
}
ll calc(char*t,int m){
	ll x=0,y=0;
	for(int i=1;i<=m;i++)
		x=(x*B1+t[i])%M1,y=(y*B2+t[i])%M2;
	return x*M2+y;
}
