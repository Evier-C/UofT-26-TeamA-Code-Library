/**
 * Description: 实矩阵行列式 (高斯消元). $a$ 会被破坏; 奇异时可能返回很小的数而不是 0,
 * 结果可能溢出 double. 整数矩阵取模用 IntDeterminant.
 * Usage: // 填 a[1..n][1..n], 多组数据重新填
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
