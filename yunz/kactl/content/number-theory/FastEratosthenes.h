/**
 * Description: 线性筛 (欧拉筛), 一次求出 $[1, n]$ 内的质数, 欧拉函数 $\varphi$
 * 和莫比乌斯函数 $\mu$. 每个合数只被它的最小质因子筛掉一次.
 * 积性函数都可以这样筛: 分 $i \bmod p = 0$ 和不等于 0 两种情况.
 * Usage: sieve(n); // n < N, 只调用一次
 * pri[1..cnt] 为质数, vis[x] = 0 且 x 至少为 2 时 x 是质数
 * phi[x], mu[x] 对 1 到 n 有效
 * Time: O(N)
 * Memory: N = 1e7 时约 130MB, 不需要的数组可以删掉
 */
#pragma once

const int N=1e7+5;
int pri[N],cnt,phi[N],mu[N];
bool vis[N];
void sieve(int n){
	phi[1]=mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i])pri[++cnt]=i,phi[i]=i-1,mu[i]=-1;
		for(int j=1;j<=cnt&&(ll)i*pri[j]<=n;j++){
			int x=i*pri[j];
			vis[x]=1;
			if(i%pri[j]==0){ // pri[j] 是 i 的最小质因子
				phi[x]=phi[i]*pri[j],mu[x]=0;
				break;
			}
			phi[x]=phi[i]*(pri[j]-1),mu[x]=-mu[i];
		}
	}
}
