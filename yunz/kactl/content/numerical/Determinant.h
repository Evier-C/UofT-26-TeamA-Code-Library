/**
 * Description: 高斯消元 (列主元) 求实矩阵的行列式. 下标从 1 开始,
 * $a[1..n][1..n]$ 会被破坏. 整数矩阵取模请用 IntDeterminant.
 * Usage: // 填好 a[1..n][1..n], 多组数据重新填即可
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
			if(fabs(a[j][i])>fabs(a[p][i]))p=j;
		if(a[p][i]==0)return 0;
		if(p!=i)swap(a[p],a[i]),res=-res;
		res*=a[i][i];
		for(int j=i+1;j<=n;j++){
			double t=a[j][i]/a[i][i];
			if(t!=0)
				for(int k=i;k<=n;k++)a[j][k]-=t*a[i][k];
		}
	}
	return res;
}
