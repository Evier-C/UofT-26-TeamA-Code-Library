/**
 * Description: 后缀数组, 倍增 + 基数排序. 输入串 s[1..n] 为 1-indexed.
 * getsa(s,n) 求 sa[1..n] 与 rk[1..n]: sa[i] 为排名第 i 小的后缀的起点,
 * rk[i] 为后缀 s[i..n] 的排名, 排名从 1 开始, 有 sa[rk[i]] = i.
 * getheight(s,n) 需在 getsa 之后调用, 求 height[1..n]:
 * height[i] 为后缀 sa[i] 与 sa[i-1] 的最长公共前缀长度, height[1] = 0.
 * 任意两后缀 i, j 的 LCP: 设 $rk_i<rk_j$, 为 height[rk[i]+1..rk[j]] 的最小值, 配 ST 表 O(1) 查询.
 * 本质不同子串数为 $n(n+1)/2-\sum height_i$.
 * 字符需在 1..127 内, 否则改 m 为字符集大小并把字符映射到 1..m.
 * rk, tp 开 2N. 多组数据无需清空, 函数内部会清.
 * Usage: scanf("\%s",s+1);
 * int n=strlen(s+1);
 * getsa(s,n);
 * getheight(s,n);
 * for(int i=1;i<=n;i++)printf("\%d ",sa[i]);
 * ll d=1ll*n*(n+1)/2; // 本质不同子串数
 * for(int i=1;i<=n;i++)d-=height[i];
 * Time: O(n \log n)
 */
#pragma once

const int N=1e6+5; // 串长上限
int sa[N],rk[N*2],tp[N*2],cnt[N],height[N];
void getsa(char*s,int n){
	int m=127; // 字符集大小
	for(int i=1;i<=2*n;i++){
		rk[i]=0;
		tp[i]=0;
	}
	for(int i=0;i<=m;i++)cnt[i]=0;
	for(int i=1;i<=n;i++){
		rk[i]=s[i];
		cnt[rk[i]]++;
	}
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--)sa[cnt[rk[i]]--]=i;
	for(int w=1;;w<<=1){
		// tp: 按第二关键字排好的后缀
		int p=0;
		for(int i=n-w+1;i<=n;i++)tp[++p]=i;
		for(int i=1;i<=n;i++){
			if(sa[i]>w)tp[++p]=sa[i]-w;
		}
		// 按第一关键字 rk 做稳定计数排序
		for(int i=0;i<=m;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[rk[i]]++;
		for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--)sa[cnt[rk[tp[i]]]--]=tp[i];
		// tp 改存旧的 rk, 重新编号
		for(int i=1;i<=n;i++)tp[i]=rk[i];
		p=0;
		for(int i=1;i<=n;i++){
			int x=sa[i];
			int y=sa[i-1];
			bool same=i>1&&tp[x]==tp[y]&&tp[x+w]==tp[y+w];
			rk[x]=same?p:++p;
		}
		if(p==n)break; // 排名已互不相同
		m=p;
	}
}
void getheight(char*s,int n){
	for(int i=1,k=0;i<=n;i++){
		if(rk[i]==1){
			height[1]=0;
			k=0;
			continue;
		}
		if(k)k--;
		int j=sa[rk[i]-1];
		while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k])k++;
		height[rk[i]]=k;
	}
}
