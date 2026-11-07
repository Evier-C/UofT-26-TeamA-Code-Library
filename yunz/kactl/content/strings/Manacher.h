/**
 * Description: Manacher 求最长回文. 字符 \# 和代码中的两个哨兵字符不能在 s 中出现.
 * 串长上限 Manacher::N, 数组开 2N; 对象必须开在全局.
 * Usage: char s[Manacher::N]; // 全局, 从 1 开始
 * Manacher MC2; // 第二个实例也开在全局
 * scanf("\%s",s+1);
 * int n=strlen(s+1);
 * int ans=MC.manacher(s,n); // 最长回文子串长度
 * // 以 s[i] 为中心的最长奇回文长度
 * int odd=MC.p[2*i]-1;
 * // 以 s[i], s[i+1] 之间为中心的最长偶回文长度
 * int even=MC.p[2*i+1]-1;
 * // 一般地, 中心 k 处回文长 MC.p[k]-1, 起点为
 * int st=(k-MC.p[k])/2+1;
 * // 多组数据直接再调用, 无需清空
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
