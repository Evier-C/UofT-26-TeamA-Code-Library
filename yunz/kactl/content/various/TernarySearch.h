/**
 * Description: 三分法求单峰函数的最大值点.
 * 整数版 tern(l, r): 在整数区间 $[l, r]$ 上求 $f$ 的最大值点, 返回最大值点中最左的一个.
 * 要求 $f$ 在最大值左边严格上升, 右边不增 (可以有相等); 实际是二分 $f(mid) < f(mid+1)$, 每步算 2 次 $f$.
 * 如果最大值左边有平台 (相邻两个值相等), 三分会出错, 只能换方法.
 * 求最小值: 把 tern 里的 $<$ 改成 $>$ (要求左边严格下降, 右边不减).
 * 实数版 ternR(l, r): 对 $[l, r]$ 上的单峰函数 $F$ 三分 100 次, 返回最大值点 (精度远小于 $10^{-9}$ 倍区间长).
 * f 和 F 都是全局函数, 按题目改写 (可以用全局数组). 端点可以到 int 范围.
 * Usage: ll f(int x) { return ...; } // 自己写
 * int p = tern(1, n); // f(p) 最大
 * double F(double x) { return ...; } // 实数版
 * double x = ternR(0, 1e9); // F(x) 最大
 * Time: O(\log(r-l)) 次求值, 实数版 200 次
 */
#pragma once

ll f(int x){return -(ll)(x-3)*(x-3);} // 按题目改
int tern(int l,int r){
	while(l<r){
		int mid=((ll)l+r)>>1;
		if(f(mid)<f(mid+1))l=mid+1; // 最大值在 mid 右边
		else r=mid;
	}
	return l;
}
double F(double x){return -(x-1)*(x-1);} // 按题目改
double ternR(double l,double r){
	for(int it=0;it<100;it++){
		double m1=l+(r-l)/3;
		double m2=r-(r-l)/3;
		if(F(m1)<F(m2))l=m1;
		else r=m2;
	}
	return l;
}
