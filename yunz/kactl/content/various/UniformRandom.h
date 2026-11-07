/**
 * Author: folklore
 * Date: 2025-11-06
 * License: CC0
 * Source: https://codeforces.com/blog/entry/61587
 * Description:
 * 高质量的均匀整数随机数生成器。
 * Usage: int x = urand(a, b); // [a, b] 内的均匀随机整数
 * Time: 生成 1e8 个数约 400ms。
 * Status: untested
 */
// 64 位整数可用 mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int urand(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }