/**
 * Description: pb\_ds 哈希表, 比 unordered\_map 快约 3 倍, 已防 hack.
 * 键必须是整数类型; 改类型就改 gp\_hash\_table 的前两个参数.
 * Usage: h.clear(); // 多组数据清空
 * h[key] = val; h[key]++; // 不存在时先插入 0
 * auto it = h.find(key); // 只判断存在要用 find
 * if (it != h.end()) cout << it->second;
 * h.erase(key); int sz = h.size();
 * for (auto [k, v] : h) ...; // 遍历, 顺序随机
 * // 第二个表, 写在全局:
 * __gnu_pbds::gp_hash_table<ll, int, chash> h2;
 * Time: 均摊 O(1)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
struct chash{
	unsigned long long operator()(ll x)const{
		// RND: 运行时随机数, 第一次调用时生成
		static const unsigned long long RND=
			chrono::steady_clock::now().time_since_epoch().count();
		// C 为大奇数
		const unsigned long long C=(ll)(4e18*acos(0))|71;
		return __builtin_bswap64((x^RND)*C);
	}
};
__gnu_pbds::gp_hash_table<ll,int,chash>h({},{},{},{},{1<<16});
