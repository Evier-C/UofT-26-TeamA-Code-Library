/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * For range add and range sum on [l, r), use RFT (two FTs).
 * Usage: RFT f(n); f.add(l, r, v); f.query(l, r);
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

struct RFT { // 区间加, 区间和
	FT a, b;
	RFT(int n) : a(n), b(n) {}
	void add(int l, int r, ll v) { // [l, r) 都加 v
		a.update(l, v), a.update(r, -v);
		b.update(l, v * l), b.update(r, -v * r);
	}
	ll sum(int r) { // [0, r) 的和
		return a.query(r) * r - b.query(r);
	}
	ll query(int l, int r) { return sum(r) - sum(l); }
};
