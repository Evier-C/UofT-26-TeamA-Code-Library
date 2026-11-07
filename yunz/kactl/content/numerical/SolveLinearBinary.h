/**
 * Description: 解异或方程组 (模 2 线性方程组): $n$ 个方程, $m$ 个 0/1 未知数,
 * 第 $i$ 个方程为 $a_{i1} x_1 \oplus \dots \oplus a_{im} x_m = a_{i,m+1}$.
 * 填全局 bitset 数组 (下标从 1 开始): a[i] 的第 $1..m$ 位为系数, 第 $m+1$ 位
 * 为右边常数. 调用 \texttt{gaussXor(n, m)}: 无解返回 $-1$; 否则返回秩 $r$,
 * 一组解在 $x[1..m]$ (自由元取 0), 解的个数为 $2^{m-r}$.
 * 用 bitset 整行异或, 比普通高斯消元快 64 倍. 需要 $m+1 < N$.
 * $a$ 会被破坏; 多组数据先把 a[1..n] 清空 (reset).
 * Usage: for(int i=1;i<=n;i++) a[i].reset(); // 清空
 * a[i][j]=1; // 第 i 个方程含 x_j
 * a[i][m+1]=1; // 第 i 个方程右边为 1
 * int r=gaussXor(n,m); // -1 无解, 否则解在 x[1..m]
 * Time: O(nm \cdot \min(n,m) / 64)
 */
#pragma once

const int N=1005; // 方程数, 未知数上限
bitset<N>a[N];
int x[N],pos[N];
int gaussXor(int n,int m){
	int r=1; // 当前处理到第 r 行
	for(int c=1;c<=m&&r<=n;c++){
		int p=r;
		while(p<=n&&!a[p][c])
			p++;
		if(p>n)
			continue; // 自由元
		swap(a[p],a[r]);
		for(int i=1;i<=n;i++)
			if(i!=r&&a[i][c])
				a[i]^=a[r];
		pos[r]=c;
		r++;
	}
	r--; // 秩
	for(int i=r+1;i<=n;i++)
		if(a[i][m+1])
			return -1; // 出现 0 = 1
	for(int j=1;j<=m;j++)
		x[j]=0;
	for(int i=1;i<=r;i++)
		x[pos[i]]=a[i][m+1];
	return r;
}
