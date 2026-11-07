/**
 * Description: 高斯-约旦消元解实系数线性方程组 ($n$ 个方程, $m$ 个未知数).
 * 绝对值小于 eps $= 10^{-9}$ 视为 0, 按数据范围调整. $a$ 会被破坏.
 * Usage: // a[i][1..m] 为第 i 个方程的系数, a[i][m+1] 为常数
 * // 填 a[1..n][1..m+1], 多组数据重新填
 * int r=gauss(n,m); // 秩, 无解为 -1
 * if(r==-1) puts("No Solution");
 * else if(r<m) puts("Infinite"); // 自由元取 0 的解在 x[1..m]
 * else ... // 唯一解 x[1..m]
 * // pos[1..r] 为主元所在的列, 其余列为自由元
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
