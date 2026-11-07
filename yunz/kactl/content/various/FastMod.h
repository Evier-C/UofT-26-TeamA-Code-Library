/**
 * Author: Simon Lindholm
 * Date: 2020-05-30
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Barrett_reduction
 * Description: 计算 $a \% b$，比普通取模快约 5 倍，适用于 $b$ 为常量但编译期未知的情形。
 * 返回值与 $a$ 模 $b$ 同余（$a \pmod b$），范围为 $[0, 2b)$。
 * Usage: FastMod F(b); ull r = F.reduce(a); // r 在 [0, 2b) 内
 * Status: proven correct, stress-tested
 * Measured as having 4 times lower latency, and 8 times higher throughput, see stress-test.
 * Details:
 * More precisely, it can be proven that the result equals 0 only if $a = 0$,
 * and otherwise lies in $[1, (1 + a/2^64) * b)$.
 */
#pragma once

typedef unsigned long long ull;
struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(-1ULL / b) {}
	ull reduce(ull a) { // a % b + (0 或 b)
		return a - (ull)((__uint128_t(m) * a) >> 64) * b;
	}
};
