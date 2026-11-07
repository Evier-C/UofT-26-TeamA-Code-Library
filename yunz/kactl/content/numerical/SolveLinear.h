/**
 * Description: 高斯-约旦消元解实系数线性方程组: $n$ 个方程, $m$ 个未知数.
 * 填全局数组 (下标从 1 开始): $a[i][1..m]$ 为第 $i$ 个方程的系数,
 * $a[i][m+1]$ 为等号右边的常数. 调用 \texttt{gauss(n, m)}:
 * 无解返回 $-1$; 否则返回系数矩阵的秩 $r$, 一组解在 $x[1..m]$.
 * $r = m$ 时解唯一; $r < m$ 时有无穷多解, 返回的是自由元都取 0 的那组,
 * pos[1..r] 为各主元所在的列 (其余列是自由元).
 * 按列选绝对值最大的主元, 绝对值小于 eps $= 10^{-9}$ 视为 0;
 * 数据范围大时按需调 eps. $a$ 会被破坏, 多组数据重新填即可.
 * Usage: // 填 a[1..n][1..m+1]
 * int r=gauss(n,m);
 * if(r==-1) puts("No Solution");
 * else if(r<m) puts("Infinite"); // 仍可用 x[1..m]
 * else ... // 唯一解 x[1..m]
 * Time: O(nm \cdot \min(n,m))
 */
#pragma once

const int N=505; // 方程数, 未知数上限
const double eps=1e-9;
double a[N][N],x[N];
int pos[N];
int gauss(int n,int m){
	int r=1; // 当前处理到第 r 行
	for(int c=1;c<=m&&r<=n;c++){
		int p=r; // 选第 c 列绝对值最大的主元
		for(int i=r+1;i<=n;i++)
			if(fabs(a[i][c])>fabs(a[p][c]))
				p=i;
		if(fabs(a[p][c])<eps)
			continue; // 自由元
		swap(a[p],a[r]);
		for(int i=1;i<=n;i++){
			if(i==r||a[i][c]==0)
				continue;
			double t=a[i][c]/a[r][c];
			for(int j=c;j<=m+1;j++)
				a[i][j]-=t*a[r][j];
		}
		pos[r]=c;
		r++;
	}
	r--; // 秩
	for(int i=r+1;i<=n;i++)
		if(fabs(a[i][m+1])>eps)
			return -1; // 出现 0 = 非 0
	for(int j=1;j<=m;j++)
		x[j]=0;
	for(int i=1;i<=r;i++)
		x[pos[i]]=a[i][m+1]/a[i][pos[i]];
	return r;
}
