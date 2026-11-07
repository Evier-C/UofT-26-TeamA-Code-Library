/**
 * Description: Z 函数, 即扩展 KMP. 串长上限 Zfunc::N; 数组很大, 对象必须开在全局.
 * exkmp 用的是同一对象里 t 的 z, 两次调用之间不能再对别的串 getz.
 * Usage: char s[Zfunc::N],t[Zfunc::N]; // 全局, 从 1 开始
 * Zfunc Z2; // 第二个实例也开在全局
 * scanf("\%s\%s",s+1,t+1);
 * int n=strlen(s+1),m=strlen(t+1);
 * Z.getz(s,n);
 * // Z.z[i]: s[i..n] 与 s 的 LCP, 约定 Z.z[1]=n
 * Z.getz(t,m); // exkmp 之前先求 t 的 z
 * Z.exkmp(s,n,t,m);
 * // Z.ext[i]: s[i..n] 与 t[1..m] 的 LCP
 * for(int i=1;i<=n;i++)
 *   if(Z.ext[i]==m)printf("\%d ",i); // t 出现在 i
 * // 多组数据直接再调用, 无需清空
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
