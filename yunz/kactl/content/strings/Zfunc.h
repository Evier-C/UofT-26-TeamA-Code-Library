/**
 * Description: Z 函数, 即扩展 KMP. 串均为 1-indexed, 放在 char 数组 s[1..n], t[1..m] 中.
 * 封装在 struct Zfunc 中, 全局对象为 Z. 数组很大, 对象必须开成全局或 static.
 * Z.getz(s,n) 求 Z.z[1..n]: z[i] 为后缀 s[i..n] 与整个 s 的最长公共前缀长度, 约定 z[1] = n.
 * 例: abacaba 得 7 0 1 0 3 0 1.
 * Z.exkmp(s,n,t,m) 求 Z.ext[1..n]: ext[i] 为 s[i..n] 与 t[1..m] 的最长公共前缀长度.
 * 它要用到 t 的 z 数组, 所以必须先对同一对象调用 getz(t,m), 且之后不能再对别的串调用 getz.
 * ext[i] = m 表示 t 在 s 的位置 i 出现. Zfunc::N 为串长上限, 多组数据无需清空.
 * Usage: char s[Zfunc::N],t[Zfunc::N]; // 全局
 * scanf("\%s\%s",s+1,t+1);
 * int n=strlen(s+1),m=strlen(t+1);
 * Z.getz(s,n); // Z.z[1..n], s 自己的 z 函数
 * Z.getz(t,m); // 先求 t 的 z
 * Z.exkmp(s,n,t,m); // 得到 Z.ext[1..n]
 * for(int i=1;i<=n;i++)
 *   if(Z.ext[i]==m)printf("\%d ",i);
 * // 第二个实例也开在全局: Zfunc Z2;
 * Time: O(n+m)
 */
#pragma once

struct Zfunc{
	static const int N=1e6+5; // 串长上限
	int z[N],ext[N];
	void getz(char*s,int n){
		z[1]=n;
		// [l,r] 为当前右端点最大的匹配段
		for(int i=2,l=0,r=0;i<=n;i++){
			z[i]=i<=r?min(z[i-l+1],r-i+1):0;
			while(i+z[i]<=n&&s[1+z[i]]==s[i+z[i]])z[i]++;
			if(i+z[i]-1>r){
				l=i;
				r=i+z[i]-1;
			}
		}
	}
	// 需先 getz(t,m)
	void exkmp(char*s,int n,char*t,int m){
		for(int i=1,l=0,r=0;i<=n;i++){
			ext[i]=i<=r?min(z[i-l+1],r-i+1):0;
			while(i+ext[i]<=n&&ext[i]<m&&s[i+ext[i]]==t[1+ext[i]]){
				ext[i]++;
			}
			if(i+ext[i]-1>r){
				l=i;
				r=i+ext[i]-1;
			}
		}
	}
}Z;
