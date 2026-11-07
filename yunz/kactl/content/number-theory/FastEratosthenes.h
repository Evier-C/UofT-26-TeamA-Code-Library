/**
 * Description: 线性筛, 同时求质数, 欧拉函数, 莫比乌斯函数 ($n < N$).
 * sieve 只能调用一次 (cnt 不清零), 取所有数据的最大 $n$. $N = 10^7$ 时约 130MB, 不需要的 phi 或 mu 可以删掉.
 * Usage: sieve(10000000); // 只调用一次
 * for(int i = 1; i <= cnt; i++) pri[i]; // 从小到大的质数
 * bool isp = x >= 2 \&\& !vis[x]; // x 是不是质数
 * phi[x]; mu[x]; // 欧拉函数, 莫比乌斯函数, x 从 1 到 n
 * Time: O(n)
 */
#pragma once

const int N=1e7+5;
int pri[N],cnt,phi[N],mu[N];
bool vis[N];
void sieve(int n){
	phi[1]=1;
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			pri[++cnt]=i;
			phi[i]=i-1;
			mu[i]=-1;
		}
		for(int j=1;j<=cnt&&(ll)i*pri[j]<=n;j++){
			int x=i*pri[j];
			vis[x]=1;
			if(i%pri[j]==0){ // pri[j] 是 i 的最小质因子
				phi[x]=phi[i]*pri[j];
				mu[x]=0;
				break;
			}
			phi[x]=phi[i]*(pri[j]-1);
			mu[x]=-mu[i];
		}
	}
}
