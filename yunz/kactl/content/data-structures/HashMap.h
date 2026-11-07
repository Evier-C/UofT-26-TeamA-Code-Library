/**
 * Description: pb\_ds 哈希表 h, 用法同 unordered\_map, 但快约 3 倍.
 * 键为 ll, 值为 int; 要别的类型就改 gp\_hash\_table 的前两个参数,
 * 键必须是整数类型, 因为 chash 只会哈希整数.
 * chash 让高位也参与哈希; 其中 RND 是运行时的随机数, 防 CodeForces 上的 hack.
 * 要第二个表就照最后一行在全局再定义一个, 见 Usage.
 * 初始容量 $2^{16}$, 必须是 2 的幂. h[key] 在键不存在时会插入值 0.
 * 只判断存在请用 h.find(key) != h.end(), 不要用 h[key], 否则会插入.
 * 注意: 内存约为 unordered\_map 的 1.5 倍; 遍历顺序是随机的.
 * Usage: h.clear(); // 多组数据清空
 * h[key] = val; h[key]++; // 插入或修改
 * auto it = h.find(key);
 * if (it != h.end()) cout << it->second; // 存在则输出值
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
