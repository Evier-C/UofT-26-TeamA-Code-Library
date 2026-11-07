/**
 * Description: 线性筛 (欧拉筛). 一次求出 $[1, n]$ 内所有质数, 欧拉函数 $\varphi$ 和莫比乌斯函数 $\mu$.
 * 每个合数 $x = i \cdot p$ 只被它的最小质因子 $p$ 筛一次, 所以是 $O(n)$.
 * 调用 sieve(n) 后 ($n < N$): pri[1..cnt] 是从小到大的质数, cnt 是个数;
 * $x \ge 2$ 时 vis[x] 为 0 表示 $x$ 是质数 (vis[0], vis[1] 也是 0, 自己特判);
 * phi[x] 和 mu[x] 对 $1 \le x \le n$ 有效.
 * 其他积性函数也这样筛: 分 $i \bmod p = 0$ ($p$ 整除 $i$) 和 $i \bmod p \neq 0$ ($p$ 与 $i$ 互质) 两种情况.
 * 注意: sieve 只能调用一次 (cnt 不清零), 取题目所有数据的最大 $n$.
 * $N = 10^7$ 时四个数组约 130MB, 不需要的 phi 或 mu 可以删掉.
 * Usage: sieve(10000000); // 只调用一次
 * for(int i = 1; i <= cnt; i++) pri[i]; // 第 i 个质数
 * bool isp = x >= 2 \&\& !vis[x]; // x 是不是质数
 * phi[x]; mu[x]; // 欧拉函数, 莫比乌斯函数
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
