/**
 * Description: 求整数矩阵行列式模 $p$. 用辗转相除消元, 不需要求逆元,
 * 所以 $p$ 不必是素数 (如矩阵树定理模合数). 要求 $p^2$ 不超过 long long.
 * 下标从 1 开始, $a[1..n][1..n]$ 会被破坏. 可以有负数.
 * Usage: // 填好 a[1..n][1..n], 多组数据重新填即可
 * ll d=detMod(n,p); // 结果在 [0,p) 内
 * Time: O(n^2 (n + \log p))
 */
#pragma once

const int N=505; // 矩阵大小上限
ll a[N][N];
ll detMod(int n,ll p){
	ll res=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)a[i][j]=(a[i][j]%p+p)%p;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++)
			while(a[j][i]){ // 辗转相除, 把 a[j][i] 消成 0
				ll t=a[i][i]/a[j][i];
				for(int k=i;k<=n;k++)
					a[i][k]=(a[i][k]+(p-t)*a[j][k])%p;
				swap(a[i],a[j]);
				res=p-res;
			}
		if(a[i][i]==0)return 0;
		res=res*a[i][i]%p;
	}
	return res%p;
}
