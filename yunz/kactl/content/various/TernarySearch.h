/**
 * Description: 三分. 整数版 tern 在 $[l, r]$ 中找 $f$ 的最大值点, 要求 $f$
 * 先严格上升, 到最大值后不增 (二分 $f(mid) < f(mid+1)$). 返回最大值点中最左的.
 * 求最小值把 < 改成 >. 若有平台不能用三分. 实数版 ternR 对单峰的 F 三分 100 次.
 * Usage: ll f(int x){...} // 自己写, 全局函数
 * int p = tern(1, n); // f(p) 为最大值
 * double x = ternR(lo, hi); // 实数版, F(x) 最大
 * Time: O(\log(r-l)) 次求值
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
		double m1=l+(r-l)/3,m2=r-(r-l)/3;
		if(F(m1)<F(m2))l=m1;
		else r=m2;
	}
	return l;
}
