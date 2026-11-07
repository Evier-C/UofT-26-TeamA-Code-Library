/**
 * Description: 字符串哈希, 双模数. 输入串 s[1..n] 为 1-indexed.
 * 封装在 struct Hash 中, 全局对象为 H. 数组很大, 对象必须开成全局或 static.
 * 一个对象存一个串的前缀哈希; 要同时处理两个串, 就开两个对象.
 * H.build(s,n) 预处理前缀哈希 h1, h2 与幂次 p1, p2. H.get(l,r) 返回子串 s[l..r] 的哈希,
 * H.calc(t,m) 返回另一个串 t[1..m] 整体的哈希, 二者可直接比较.
 * 两个模数的结果合成一个 ll 返回, 可直接比较或放进 map, set, unordered\_map.
 * 不同对象的 get 结果也可直接比较, 因为模数和底数相同.
 * 冲突: 双模单次冲突概率约 $10^{-18}$, 很安全. 单模 $10^9+7$ 比较约 $10^5$ 个串时
 * 就可能因生日悖论冲突; 自然溢出 unsigned long long 最快, 但会被 Thue-Morse 串卡掉.
 * 怕被 hack 时把 B1, B2 换成随机数.
 * 注意: 字符值不能为 0, 例如不要存 s[i]-'a', 否则 a 与 aa 等长度不同的串可能同哈希.
 * 串长上限为 Hash::N. 多组数据直接再 build.
 * Usage: char s[Hash::N],t[Hash::N]; // 全局
 * scanf("\%s\%s",s+1,t+1);
 * int n=strlen(s+1),m=strlen(t+1);
 * H.build(s,n);
 * // 判断 s[l1..r1] 与 s[l2..r2] 是否相同
 * bool same=H.get(l1,r1)==H.get(l2,r2);
 * ll ht=H.calc(t,m); // t[1..m] 的哈希
 * bool occ=H.get(l,l+m-1)==ht; // t 是否在位置 l 出现
 * // 第二个串用第二个对象, 也开在全局: Hash H2;
 * H2.build(t,m);
 * bool eq=H.get(l1,r1)==H2.get(l2,r2);
 * Time: 预处理 O(n), 查询 O(1)
 */
#pragma once

struct Hash{
	static const int N=1e6+5; // 串长上限
	static const int M1=1e9+7,M2=998244353;
	static const int B1=131,B2=13331;
	int h1[N],h2[N],p1[N],p2[N];
	void build(char*s,int n){
		p1[0]=1;
		p2[0]=1;
		h1[0]=0;
		h2[0]=0;
		for(int i=1;i<=n;i++){
			p1[i]=1ll*p1[i-1]*B1%M1;
			p2[i]=1ll*p2[i-1]*B2%M2;
			h1[i]=(1ll*h1[i-1]*B1+s[i])%M1;
			h2[i]=(1ll*h2[i-1]*B2+s[i])%M2;
		}
	}
	// s[l..r] 的哈希
	ll get(int l,int r){
		ll x=(h1[r]-1ll*h1[l-1]*p1[r-l+1]%M1+M1)%M1;
		ll y=(h2[r]-1ll*h2[l-1]*p2[r-l+1]%M2+M2)%M2;
		return x*M2+y;
	}
	// t[1..m] 整体的哈希
	ll calc(char*t,int m){
		ll x=0,y=0;
		for(int i=1;i<=m;i++){
			x=(x*B1+t[i])%M1;
			y=(y*B2+t[i])%M2;
		}
		return x*M2+y;
	}
}H;
