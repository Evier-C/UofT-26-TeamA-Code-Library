/**
 * Description: Manacher. 在 s[1..n] 的字符间插入 \# 得到 a[1..m] ($m = 2n+1$):
 * a[2i] = s[i], 奇数位为 \#. p[k] 为 a 中以 k 为中心的最长回文半径, 含中心;
 * 对应原串中的回文长度为 p[k]-1, 起点为 (k-p[k])/2+1.
 * 以 s[i] 为中心的最长奇回文长 p[2i]-1, 以 s[i], s[i+1] 之间为中心的最长偶回文长 p[2i+1]-1.
 * Usage: int len=manacher(s,n); // 最长回文子串长度
 * // 多组数据直接再调用
 * Time: O(n)
 */
#pragma once

const int N=1e6+5; // 串长上限
char a[N*2];int p[N*2];
int manacher(char*s,int n){
	int m=0;a[0]='$';a[++m]='#';
	for(int i=1;i<=n;i++)a[++m]=s[i],a[++m]='#';
	a[m+1]='@'; // 两端哨兵, 不能在 s 中出现
	int ans=0;
	for(int i=1,mid=0,r=0;i<=m;i++){
		p[i]=i<r?min(p[2*mid-i],r-i):1;
		while(a[i+p[i]]==a[i-p[i]])p[i]++;
		if(i+p[i]>r)r=i+p[i],mid=i;
		ans=max(ans,p[i]-1);
	}
	return ans;
}
