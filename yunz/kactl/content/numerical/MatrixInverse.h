/**
 * Description: 高斯-约旦消元求实矩阵的逆. 下标从 1 开始, 把 $a[1..n][1..n]$
 * 右边拼上单位阵 $a[1..n][n+1..2n]$ 一起消元. 可逆返回 true 且 $a[1..n][1..n]$
 * 变为逆矩阵; 奇异返回 false. 模素数版本: 主元选任意非 0 元,
 * 除法改为乘逆元 qpow(v, MOD-2), 所有运算取模. 模 $p^k$: 设 $B$ 为模 $p$
 * 的逆, 反复 $B = B(2I - AB)$, 每次模数指数 $k$ 翻倍.
 * Usage: // 填好 a[1..n][1..n], 多组数据重新填即可
 * if(inverse(n)) ... // 逆矩阵在 a[1..n][1..n]
 * Time: O(n^3)
 */
#pragma once

const int N=505; // 矩阵大小上限
double a[N][N*2];
bool inverse(int n){
	for(int i=1;i<=n;i++)
		for(int j=n+1;j<=2*n;j++)a[i][j]=(j-n==i);
	for(int i=1;i<=n;i++){
		int p=i; // 选绝对值最大的主元
		for(int j=i+1;j<=n;j++)
			if(fabs(a[j][i])>fabs(a[p][i]))p=j;
		if(fabs(a[p][i])<1e-12)return false;
		swap(a[i],a[p]);
		double t=1/a[i][i];
		for(int j=1;j<=2*n;j++)a[i][j]*=t;
		for(int k=1;k<=n;k++)
			if(k!=i&&a[k][i]!=0){
				double v=a[k][i];
				for(int j=1;j<=2*n;j++)a[k][j]-=v*a[i][j];
			}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)a[i][j]=a[i][j+n];
	return true;
}
