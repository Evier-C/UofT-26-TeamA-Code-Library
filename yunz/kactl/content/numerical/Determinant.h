/**
 * Description: 求 $n \times n$ 实矩阵的行列式 (高斯消元, 列主元).
 * 填全局数组 $a[1..n][1..n]$ (下标从 1 开始), \texttt{det(n)} 返回行列式.
 * 消成上三角, 行列式 = 主对角线之积, 每交换一次两行变号.
 * $a$ 会被破坏; 多组数据重新填即可. 奇异矩阵可能返回很小的数而不是 0.
 * 结果可能很大 (溢出 double 范围时考虑改 long double 或取对数).
 * 整数矩阵求模意义下的行列式 (如矩阵树定理) 用 IntDeterminant.
 * Usage: // 填 a[1..n][1..n]
 * double d=det(n);
 * Time: O(n^3)
 */
#pragma once

const int N=505; // 矩阵大小上限
double a[N][N];
double det(int n){
	double res=1;
	for(int i=1;i<=n;i++){
		int p=i; // 选绝对值最大的主元
		for(int j=i+1;j<=n;j++)
			if(fabs(a[j][i])>fabs(a[p][i]))
				p=j;
		if(a[p][i]==0)
			return 0;
		if(p!=i){
			swap(a[p],a[i]);
			res=-res;
		}
		res*=a[i][i];
		for(int j=i+1;j<=n;j++){
			double t=a[j][i]/a[i][i];
			if(t==0)
				continue;
			for(int k=i;k<=n;k++)
				a[j][k]-=t*a[i][k];
		}
	}
	return res;
}
