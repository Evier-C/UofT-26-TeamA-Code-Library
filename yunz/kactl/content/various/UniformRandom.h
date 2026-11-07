/**
 * Description: 随机数. rng 是 64 位的 mt19937\_64, 用当前时间做种子 (每次运行不同, 防止被 hack).
 * rnd(l, r) 返回 $[l, r]$ 内均匀随机的整数 (闭区间, 要求 $l \le r$, 可以到 long long 范围).
 * 不要用 rand(): 在 Windows 上最大只有 32767, 而且质量差.
 * 调试时想固定结果, 把种子改成常数, 如 rng(12345).
 * Usage: ll x = rnd(1, 100); // [1, 100] 内的随机整数
 * shuffle(a + 1, a + n + 1, rng); // 随机打乱 a[1..n]
 * double y = uniform_real_distribution<double>(0, 1)(rng);
 * unsigned long long h = rng(); // 64 位随机数, 可做哈希
 * Time: O(1)
 */
#pragma once

mt19937_64 rng(chrono::steady_clock::now()
	.time_since_epoch().count());
ll rnd(ll l,ll r){ // [l, r] 内均匀随机
	return uniform_int_distribution<ll>(l,r)(rng);
}
