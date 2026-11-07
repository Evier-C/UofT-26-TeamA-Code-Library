/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * License: CC0
 * Source: Russian page
 * Description: 预处理模逆元。要求 LIM $\le$ mod 且 mod 为质数。
 * Usage: // 下面的代码需放在 main 等函数内
 * inv[i]; // 1 到 LIM-1 中 i 模 mod 的逆元
 * Status: Works
 */
#pragma once

// const ll mod = 1000000007, LIM = 200000; ///include-line
ll* inv = new ll[LIM] - 1; inv[1] = 1;
rep(i,2,LIM) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
