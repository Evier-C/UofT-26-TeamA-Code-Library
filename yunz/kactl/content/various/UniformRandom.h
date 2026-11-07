/**
 * Description: 随机数, 用时间做种子. 不要用 rand(). 调试时把种子改成常数.
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
