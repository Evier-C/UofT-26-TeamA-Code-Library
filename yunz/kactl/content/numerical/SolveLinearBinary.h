/**
 * Description: 解异或方程组 (模 2), $n$ 个方程 $m$ 个 0/1 未知数, 需要 $m+1 < N$.
 * $a$ 会被破坏.
 * Usage: for(int i=1;i<=n;i++) a[i].reset(); // 每组数据先清空
 * a[i][j]=1; // 第 i 个方程含 x_j (j 从 1 到 m)
 * a[i][m+1]=1; // 第 i 个方程右边为 1
 * int r=gaussXor(n,m); // 秩, 无解为 -1
 * // 有解时一组解在 x[1..m], 自由元取 0, 共 2^(m-r) 组
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
