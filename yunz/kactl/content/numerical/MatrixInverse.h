/**
 * Description: 求 $n \times n$ 实矩阵的逆 (高斯-约旦消元, 列主元).
 * 填全局数组 $a[1..n][1..n]$ (下标从 1 开始), 调用 \texttt{inverse(n)}:
 * 可逆返回 true, 且 $a[1..n][1..n]$ 变为逆矩阵; 奇异返回 false ($a$ 被破坏).
 * 做法: 右边拼上单位阵 $a[1..n][n+1..2n]$, 把左半边消成单位阵, 右半边即逆.
 * 主元绝对值小于 $10^{-12}$ 视为奇异 (数值大小差很多时按需调整).
 * 模素数版本: double 改 ll, 主元选任意非 0 元, 除以 $v$ 改为乘
 * qpow(v, MOD-2), 所有加减乘取模. 模 $p^k$: 先求模 $p$ 的逆 $B$,
 * 反复令 $B = B(2I - AB)$, 每次模数的指数 $k$ 翻倍.
 * Usage: // 填 a[1..n][1..n]
 * if(inverse(n)) ... // 逆矩阵在 a[1..n][1..n]
 * else puts("No Solution"); // 奇异
 * Time: O(n^3)
 */
#pragma once

const int N=505; // 矩阵大小上限
double a[N][N*2];
bool inverse(int n){
	for(int i=1;i<=n;i++)
		for(int j=n+1;j<=2*n;j++)
			a[i][j]=(j-n==i);
	for(int i=1;i<=n;i++){
		int p=i; // 选绝对值最大的主元
		for(int j=i+1;j<=n;j++)
			if(fabs(a[j][i])>fabs(a[p][i]))
				p=j;
		if(fabs(a[p][i])<1e-12)
			return false;
		swap(a[i],a[p]);
		double t=1/a[i][i];
		for(int j=1;j<=2*n;j++)
			a[i][j]*=t;
		for(int k=1;k<=n;k++){
			if(k==i||a[k][i]==0)
				continue;
			double v=a[k][i];
			for(int j=1;j<=2*n;j++)
				a[k][j]-=v*a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=a[i][j+n];
	return true;
}
