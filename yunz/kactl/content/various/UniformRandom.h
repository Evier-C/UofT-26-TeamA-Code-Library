/**
 * Description: 随机数. mt19937\_64 用时间做种子 (防 hack), 不要用 rand().
 * Usage: ll x = rnd(1, 100); // [1, 100] 内均匀随机整数
 * shuffle(a + 1, a + n + 1, rng); // 随机打乱 a[1..n]
 * double y = uniform_real_distribution<double>(0, 1)(rng);
 * Time: O(1)
 */
#pragma once

mt19937_64 rng(chrono::steady_clock::now()
	.time_since_epoch().count());
ll rnd(ll l,ll r){ // [l, r] 内均匀随机
	return uniform_int_distribution<ll>(l,r)(rng);
}
