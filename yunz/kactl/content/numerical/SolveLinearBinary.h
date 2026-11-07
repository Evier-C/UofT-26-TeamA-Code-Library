/**
 * Description: 异或方程组 (模 2 线性方程组), 用 bitset 做高斯消元.
 * 下标从 1 开始: a[i] 的第 $1..m$ 位为系数, 第 $m+1$ 位为常数项.
 * 无解返回 -1; 否则返回秩 $r$, $x[1..m]$ 为一组解 ($r < m$ 时有
 * $2^{m-r}$ 组解, 自由元取 0). $a$ 会被破坏. 需要 $m+1 < N$.
 * Usage: for(int i=1;i<=n;i++) a[i].reset(); // 多组数据清空
 * a[i][j]=1; a[i][m+1]=b_i; // 第 i 个方程
 * int r=gaussXor(n,m); // 解在 x[1..m]
 * Time: O(nm \cdot \min(n,m) / 64)
 */
#pragma once

const int N=1005; // 方程数, 未知数上限
bitset<N>a[N];
int x[N],pos[N];
int gaussXor(int n,int m){
	int r=1; // 当前行
	for(int c=1;c<=m&&r<=n;c++){
		int p=r;
		while(p<=n&&!a[p][c])p++;
		if(p>n)continue; // 自由元
		swap(a[p],a[r]);
		for(int i=1;i<=n;i++)
			if(i!=r&&a[i][c])a[i]^=a[r];
		pos[r++]=c;
	}
	r--; // 秩
	for(int i=r+1;i<=n;i++)
		if(a[i][m+1])return -1; // 0 = 1
	for(int j=1;j<=m;j++)x[j]=0;
	for(int i=1;i<=r;i++)x[pos[i]]=a[i][m+1];
	return r;
}
