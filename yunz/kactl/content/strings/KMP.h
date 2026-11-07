/**
 * Description: KMP. 串均为 1-indexed. nxt[i] 为 t[1..i] 的最长真 border 长度,
 * 即既是前缀又是后缀, 且不等于 t[1..i] 本身的最长串. 例: abacaba 得 0 0 1 0 1 2 3.
 * kmp 求出 t 在 s 中所有出现的起点.
 * Usage: scanf("%s%s",s+1,t+1);n=strlen(s+1);m=strlen(t+1);
 * vector<int> occ=kmp(s,n,t,m); // 起点, 升序; 同时求出 nxt
 * getnxt(t,m); // 只要前缀函数时
 * // 最小周期: m-nxt[m]
 * Time: O(n+m)
 */
#pragma once

const int N=1e6+5; // 串长上限
int nxt[N];
void getnxt(char*t,int m){
	nxt[1]=0;
	for(int i=2,j=0;i<=m;i++){
		while(j&&t[i]!=t[j+1])j=nxt[j];
		if(t[i]==t[j+1])j++;
		nxt[i]=j;
	}
}
// t 在 s 中出现的所有起点
vector<int>kmp(char*s,int n,char*t,int m){
	getnxt(t,m);
	vector<int>res;
	for(int i=1,j=0;i<=n;i++){
		while(j&&s[i]!=t[j+1])j=nxt[j];
		if(s[i]==t[j+1])j++;
		if(j==m)res.push_back(i-m+1),j=nxt[j];
	}
	return res;
}
