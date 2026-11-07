/**
 * Description: 双模数字符串哈希, 结果为 ll, 可直接比较或放进 map, set.
 * 双模冲突概率约 $10^{-18}$; 单模在约 $10^5$ 个串时就会因生日悖论冲突, 自然溢出会被 Thue-Morse 串卡;
 * 怕被 hack 时把 B1, B2 换成随机数. 字符值不能为 0, 不要存 s[i]-'a'.
 * 串长上限 Hash::N; 对象必须开在全局, 一个对象存一个串.
 * Usage: char s[Hash::N],t[Hash::N]; // 全局, 从 1 开始
 * scanf("\%s\%s",s+1,t+1);
 * int n=strlen(s+1),m=strlen(t+1);
 * H.build(s,n); // 预处理 s
 * // 判断 s[l1..r1] 与 s[l2..r2] 是否相同
 * bool same=H.get(l1,r1)==H.get(l2,r2);
 * ll ht=H.calc(t,m); // 整个 t[1..m] 的哈希
 * bool occ=H.get(l,l+m-1)==ht; // t 是否在位置 l 出现
 * Hash H2; // 第二个串用第二个对象, 也开在全局
 * H2.build(t,m);
 * bool eq=H.get(l1,r1)==H2.get(l2,r2); // 可跨对象比较
 * // 多组数据直接再 build
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
