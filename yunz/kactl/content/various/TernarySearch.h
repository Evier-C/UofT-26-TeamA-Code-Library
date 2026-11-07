/**
 * Description: 三分求单峰函数的最大值点. tern 要求 $f$ 在最大值左边严格上升 (不能有平台), 右边不增.
 * 求最小值把 tern 里的 $<$ 改成 $>$.
 * Usage: ll f(int x) { return ...; } // 自己写, 全局函数
 * int p = tern(1, n); // f(p) 最大, 有多个时取最左
 * double F(double x) { return ...; } // 实数版
 * double x = ternR(0, 1e9); // F(x) 最大, 三分 100 次
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
