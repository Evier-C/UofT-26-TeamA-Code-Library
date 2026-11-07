/**
 * Description: 最小表示法. 普通函数, 无状态. 求最大表示: 把代码中比较的两个分支对调.
 * Usage: scanf("\%s",s+1); // 下标从 1 开始
 * int n=strlen(s+1);
 * // 字典序最小的循环同构串的起点, 从 1 开始
 * // 有多个起点时取最小的
 * int k=minrot(s,n);
 * // 输出最小表示 s[k..n]+s[1..k-1]
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
