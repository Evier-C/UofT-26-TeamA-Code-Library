/**
 * Description: 实矩阵求逆 (高斯-约旦消元). a 开成 $N \times 2N$ (右半边放单位阵).
 * 主元小于 $10^{-12}$ 视为奇异. 模素数版本: double 改 ll, 主元取任意非 0 元,
 * 除法改为乘逆元, 运算都取模.
 * Usage: // 填 a[1..n][1..n], 多组数据重新填
 * if(inverse(n)) ... // 可逆, 逆矩阵在 a[1..n][1..n]
 * else puts("No Solution"); // 奇异, a 被破坏
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
