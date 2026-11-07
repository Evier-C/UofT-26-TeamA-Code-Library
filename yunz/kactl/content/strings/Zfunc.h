/**
 * Description: Z 函数, 即扩展 KMP. 串均为 1-indexed.
 * z[i] 为 s[i..n] 与 s 的最长公共前缀长度, 约定 z[1] = n. (abacaba 得 7 0 1 0 3 0 1)
 * exkmp: ext[i] 为 s[i..n] 与 t[1..m] 的最长公共前缀长度.
 * Usage: getz(s,n); // z[1..n]
 * getz(t,m);exkmp(s,n,t,m); // ext[1..n], 会用到 t 的 z
 * // ext[i]==m 即 t 在 s 的位置 i 出现
 * Time: O(n+m)
 */
#pragma once

const int N=1e6+5; // 串长上限
int z[N],ext[N];
void getz(char*s,int n){
	z[1]=n;
	for(int i=2,l=0,r=0;i<=n;i++){
		z[i]=i<=r?min(z[i-l+1],r-i+1):0;
		while(i+z[i]<=n&&s[1+z[i]]==s[i+z[i]])z[i]++;
		if(i+z[i]-1>r)l=i,r=i+z[i]-1;
	}
}
// 需先 getz(t,m)
void exkmp(char*s,int n,char*t,int m){
	for(int i=1,l=0,r=0;i<=n;i++){
		ext[i]=i<=r?min(z[i-l+1],r-i+1):0;
		while(i+ext[i]<=n&&ext[i]<m&&s[i+ext[i]]==t[1+ext[i]])
			ext[i]++;
		if(i+ext[i]-1>r)l=i,r=i+ext[i]-1;
	}
}
