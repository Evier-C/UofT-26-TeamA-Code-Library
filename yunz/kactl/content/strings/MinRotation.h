/**
 * Description: 最小表示法. 输入串 s[1..n] 为 1-indexed, 把它看成环,
 * minrot(s,n) 返回字典序最小的循环同构串的起点 k, 从 1 开始;
 * 若有多个起点都能得到最小串, 返回最小的 k.
 * 最小表示即 s[k..n] 接上 s[1..k-1]. 不需要全局数组, 不需要清空.
 * 求最大表示: 把比较中的两个分支对调即可.
 * Usage: scanf("\%s",s+1);
 * int n=strlen(s+1);
 * int k=minrot(s,n);
 * for(int i=0;i<n;i++)putchar(s[(k-1+i)\%n+1]);
 * Time: O(n)
 */
#pragma once

int minrot(char*s,int n){
	// i, j 为两个候选起点, 从 0 开始; k 为已匹配长度
	int i=0,j=1,k=0;
	while(i<n&&j<n&&k<n){
		int x=s[(i+k)%n+1];
		int y=s[(j+k)%n+1];
		if(x==y){
			k++;
			continue;
		}
		// 较大的那个起点及其后 k 位都不可能是答案
		if(x>y)i+=k+1;
		else j+=k+1;
		if(i==j)j++;
		k=0;
	}
	return min(i,j)+1;
}
