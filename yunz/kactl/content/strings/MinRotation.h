/**
 * Description: 最小表示法: 求 s[1..n] 字典序最小的循环同构串的起点.
 * 若有多个起点, 返回最小的.
 * Usage: int k=minrot(s,n); // 最小表示为 s[k..n]+s[1..k-1]
 * Time: O(n)
 */
#pragma once

int minrot(char*s,int n){
	// i, j 为两个候选起点, 从 0 开始; k 为已匹配长度
	int i=0,j=1,k=0;
	while(i<n&&j<n&&k<n){
		int x=s[(i+k)%n+1],y=s[(j+k)%n+1];
		if(x==y){k++;continue;}
		if(x>y)i+=k+1;else j+=k+1;
		if(i==j)j++;
		k=0;
	}
	return min(i,j)+1;
}
