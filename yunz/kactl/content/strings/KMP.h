/**
 * Description: KMP 单模式串匹配. 串长上限 KMP::N; 数组很大, 对象必须开在全局.
 * Usage: char s[KMP::N],t[KMP::N]; // 全局, 下标从 1 开始
 * KMP K2; // 第二个实例也开在全局
 * scanf("\%s\%s",s+1,t+1);
 * int n=strlen(s+1),m=strlen(t+1);
 * // t 在 s 中所有出现的起点, 升序, 可重叠
 * vector<int> occ=K.kmp(s,n,t,m);
 * // 只要前缀函数时 (kmp 内部也会求):
 * K.getnxt(t,m);
 * // K.nxt[i]: t[1..i] 的最长真 border 长度
 * int per=m-K.nxt[m]; // t 的最小周期
 * // 多组数据直接再调用, 无需清空
 * Time: O(n+m)
 */
#pragma once

struct KMP{
	static const int N=1e6+5; // 串长上限
	int nxt[N];
	void getnxt(char*t,int m){
		nxt[1]=0;
		for(int i=2,j=0;i<=m;i++){
			while(j&&t[i]!=t[j+1])j=nxt[j];
			if(t[i]==t[j+1])j++;
			nxt[i]=j;
		}
	}
	// 返回 t 在 s 中所有出现的起点
	vector<int>kmp(char*s,int n,char*t,int m){
		getnxt(t,m);
		vector<int>res;
		for(int i=1,j=0;i<=n;i++){
			while(j&&s[i]!=t[j+1])j=nxt[j];
			if(s[i]==t[j+1])j++;
			if(j==m){
				res.push_back(i-m+1);
				j=nxt[j];
			}
		}
		return res;
	}
}K;
