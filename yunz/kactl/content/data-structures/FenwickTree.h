/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: 树状数组: 求前缀和 a[0] + a[1] + ... + a[pos - 1], 单点修改 a[i]
 * (传入新值与旧值之差). 区间加, 区间和 (都是 [l, r)) 用 RFT (两个 FT).
 * Usage: FT t(n); t.update(i, d); t.query(r); t.lower_bound(s);
 * RFT f(n); f.add(l, r, v); f.query(l, r);
 * Time: 两种操作均为 $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

struct FT{
	vector<ll>s;
	FT(int n):s(n){}
	void update(int pos,ll dif){ // a[pos] += dif
		for(;pos<sz(s);pos|=pos+1)s[pos]+=dif;
	}
	ll query(int pos){ // [0, pos) 的和
		ll res=0;
		for(;pos>0;pos&=pos-1)res+=s[pos-1];
		return res;
	}
	// 最小的 pos 使 [0, pos] 的和不小于 sum
	int lower_bound(ll sum){
		// 全部和都不够则返回 n; sum 不大于 0 返回 -1
		if(sum<=0)return -1;
		int pos=0;
		for(int pw=1<<25;pw;pw>>=1){
			if(pos+pw<=sz(s)&&s[pos+pw-1]<sum)
				pos+=pw,sum-=s[pos-1];
		}
		return pos;
	}
};

struct RFT{ // 区间加, 区间和
	FT a,b;
	RFT(int n):a(n),b(n){}
	void add(int l,int r,ll v){ // [l, r) 都加 v
		a.update(l,v),a.update(r,-v);
		b.update(l,v*l),b.update(r,-v*r);
	}
	ll sum(int r){ // [0, r) 的和
		return a.query(r)*r-b.query(r);
	}
	ll query(int l,int r){return sum(r)-sum(l);}
};
