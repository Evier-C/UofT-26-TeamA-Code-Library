/**
 * Description: pb\_ds 哈希表, 用法同 unordered\_map, 但快约 3 倍.
 * 键 ll, 值 int, 要别的类型改 gp\_hash\_table 的前两个参数.
 * chash 让高位也参与哈希; RND 为随机数, 防 CodeForces 上的 hack.
 * Usage: h[key] = val; h.erase(key); h.clear();
 * if (h.find(key) != h.end()) ...; // 判断是否存在
 * for (auto [k, v] : h) ...; // 遍历, 顺序随机
 * Time: 均摊 O(1)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
const unsigned long long RND=
	chrono::steady_clock::now().time_since_epoch().count();
struct chash{
	unsigned long long operator()(ll x)const{
		// C 为大奇数
		const unsigned long long C=(ll)(4e18*acos(0))|71;
		return __builtin_bswap64((x^RND)*C);
	}
};
__gnu_pbds::gp_hash_table<ll,int,chash>h({},{},{},{},{1<<16});
