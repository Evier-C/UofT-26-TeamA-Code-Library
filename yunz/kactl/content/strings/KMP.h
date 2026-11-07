/**
 * Description: KMP 单模式串匹配. 串均为 1-indexed, 放在 char 数组 s[1..n], t[1..m] 中.
 * 封装在 struct KMP 中, 全局对象为 K. 数组很大, 对象必须开成全局或 static, 不能放在函数里.
 * K.getnxt(t,m) 求前缀函数 K.nxt[1..m]: nxt[i] 为 t[1..i] 的最长真 border 长度,
 * 即既是前缀又是后缀, 且不等于 t[1..i] 本身的最长串的长度. 例: abacaba 得 0 0 1 0 1 2 3.
 * K.kmp(s,n,t,m) 先调用 getnxt(t,m), 再返回 t 在 s 中所有出现的起点, 按升序, 允许重叠.
 * 常用结论: t 的最小周期为 m-nxt[m]; 若它整除 m 且不等于 m, 则 t 由更短的串重复得到.
 * nxt 只对模式串 t 求, KMP::N 为串长上限. 多组数据无需清空, 直接再调用.
 * Usage: char s[KMP::N],t[KMP::N]; // 全局
 * scanf("\%s\%s",s+1,t+1);
 * int n=strlen(s+1),m=strlen(t+1);
 * vector<int> occ=K.kmp(s,n,t,m); // t 每次出现的起点
 * printf("\%d",(int)occ.size());
 * // 只要前缀函数时:
 * K.getnxt(t,m); // 之后读 K.nxt[1..m]
 * int per=m-K.nxt[m]; // 最小周期
 * // 第二个实例也开在全局: KMP K2;
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
