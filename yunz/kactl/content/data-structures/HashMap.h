/**
 * Author: Simon Lindholm, chilli
 * Date: 2018-07-23
 * License: CC0
 * Source: http://codeforces.com/blog/entry/60737
 * Description: 哈希表, 接口与 unordered\_map 基本相同, 但快约 3 倍,
 * 内存约 1.5 倍. 若指定初始容量, 必须是 2 的幂.
 * Usage: h[key] = val; h.erase(key);
 * auto it = h.find(key); // 不存在时为 h.end()
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
// 让高位也参与哈希, 而不只用低位:
struct chash { // C 取大奇数
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};
__gnu_pbds::gp_hash_table<ll,int,chash> h({},{},{},{},{1<<16});

/** 防 hack 版本, 如 CodeForces:

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { // 让高位也参与哈希:
	const uint64_t C = ll(4e18 * acos(0)) | 71; // 大奇数
	ll operator()(ll x) const { return __builtin_bswap64((x^RANDOM)*C); }
};
__gnu_pbds::gp_hash_table<ll, int, chash> h({},{},{},{}, {1 << 16});
*/
