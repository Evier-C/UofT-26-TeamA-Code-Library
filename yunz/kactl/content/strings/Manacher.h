/**
 * Description: Manacher 求每个中心的最长回文. 输入串 s[1..n] 为 1-indexed.
 * 封装在 struct Manacher 中, 全局对象为 MC. 数组很大, 对象必须开成全局或 static.
 * MC.manacher(s,n) 在字符间和两端插入 \#, 得到 a[1..m], $m = 2n+1$: a[2i] = s[i], 奇数位为 \#.
 * 求出 MC.p[1..m]: p[k] 为 a 中以 k 为中心的最长回文半径, 含中心.
 * 返回值为 s 的最长回文子串长度.
 * 读结果: a 中以 k 为中心的回文对应 s 中长 p[k]-1 的回文, 起点为 (k-p[k])/2+1.
 * 以 s[i] 为中心的最长奇回文长 p[2i]-1; 以 s[i], s[i+1] 之间为中心的最长偶回文长 p[2i+1]-1.
 * a[0] 与 a[m+1] 为两个不同的哨兵字符, 它们和 \# 都不能在 s 中出现.
 * a, p 开 2N, Manacher::N 为串长上限. 多组数据无需清空.
 * Usage: char s[Manacher::N]; // 全局
 * scanf("\%s",s+1);
 * int n=strlen(s+1);
 * int ans=MC.manacher(s,n); // 最长回文子串长度
 * // 以 s[i] 为中心的最长奇回文
 * int odd=MC.p[2*i]-1;
 * // 以 s[i], s[i+1] 之间为中心的最长偶回文
 * int even=MC.p[2*i+1]-1;
 * // 第二个实例也开在全局: Manacher MC2;
 * Time: O(n)
 */
#pragma once

struct Manacher{
	static const int N=1e6+5; // 串长上限
	char a[N*2];
	int p[N*2];
	int manacher(char*s,int n){
		int m=0;
		a[0]='$';
		a[++m]='#';
		for(int i=1;i<=n;i++){
			a[++m]=s[i];
			a[++m]='#';
		}
		a[m+1]='@'; // 两端哨兵不同, 扩展到边界就停
		int ans=0;
		// mid 为右端最远的回文中心, r 为其右端的下一位
		for(int i=1,mid=0,r=0;i<=m;i++){
			p[i]=i<r?min(p[2*mid-i],r-i):1;
			while(a[i+p[i]]==a[i-p[i]])p[i]++;
			if(i+p[i]>r){
				r=i+p[i];
				mid=i;
			}
			ans=max(ans,p[i]-1);
		}
		return ans;
	}
}MC;
