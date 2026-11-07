/**
 * Description: 求整数矩阵的行列式模 $p$. 填全局数组 $a[1..n][1..n]$
 * (下标从 1 开始, 可以有负数, 绝对值不超过 long long), \texttt{detMod(n, p)}
 * 返回 $\det \bmod p$, 在 $[0, p)$ 内.
 * 用辗转相除消元: 对第 $i$ 列, 每个下面的行 $j$ 与第 $i$ 行反复做
 * 第 $i$ 行减去 $\lfloor a_{ii} / a_{ji} \rfloor$ 倍的第 $j$ 行再交换, 直到 $a_{ji} = 0$
 * (像求 gcd). 不需要逆元, 所以 $p$ 不必是素数.
 * 要求 $p^2$ 不超过 long long (即 $p < 3 \cdot 10^9$). $a$ 会被破坏.
 * 常用于矩阵树定理: 填拉普拉斯矩阵去掉一行一列.
 * Usage: // 填 a[1..n][1..n]
 * ll d=detMod(n,1000000007);
 * Time: O(n^2 (n + \log p))
 */
#pragma once

const int N=505; // 矩阵大小上限
ll a[N][N];
ll detMod(int n,ll p){
	ll res=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=(a[i][j]%p+p)%p;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			while(a[j][i]){ // 辗转相除, 把 a[j][i] 消成 0
				ll t=a[i][i]/a[j][i];
				for(int k=i;k<=n;k++)
					a[i][k]=(a[i][k]+(p-t)*a[j][k])%p;
				swap(a[i],a[j]);
				res=p-res;
			}
		}
		if(a[i][i]==0)
			return 0;
		res=res*a[i][i]%p;
	}
	return res%p;
}
