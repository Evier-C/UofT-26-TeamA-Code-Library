/**
 * Description: 用 set 维护若干互不相交的整数闭区间 $[l, r]$, 相交或相邻的区间
 * 会自动合并. add 加入 $[l, r]$, del 删掉 $[l, r]$ 内所有的点
 * (可能把一个区间切成两半). tot 为被覆盖的点数.
 * Usage: add(1, 5); add(7, 9); add(6, 6); // st = {[1, 9]}
 * del(3, 4); // st = {[1, 2], [5, 9]}, tot = 7
 * auto it = getIt(x); // 包含 x 的区间, 不存在时为 st.end()
 * // 多组数据: st.clear(), tot = 0
 * Time: 均摊 O(\log N)
 */
#pragma once

set<pair<int,int>>st;
ll tot; // 被覆盖的点数
void add(int l,int r){
	auto it=st.lower_bound({l,INT_MIN});
	if(it!=st.begin()&&prev(it)->second>=l-1)it--;
	while(it!=st.end()&&it->first<=r+1){
		l=min(l,it->first),r=max(r,it->second);
		tot-=it->second-it->first+1;
		it=st.erase(it);
	}
	st.insert({l,r}),tot+=r-l+1;
}
void del(int l,int r){
	auto it=st.lower_bound({l,INT_MIN});
	if(it!=st.begin()&&prev(it)->second>=l)it--;
	while(it!=st.end()&&it->first<=r){
		auto[L,R]=*it;
		it=st.erase(it),tot-=R-L+1;
		if(L<l)st.insert({L,l-1}),tot+=l-L;
		if(R>r)st.insert({r+1,R}),tot+=R-r;
	}
}
set<pair<int,int>>::iterator getIt(int x){
	auto it=st.upper_bound({x,INT_MAX});
	if(it==st.begin()||prev(it)->second<x)return st.end();
	return prev(it);
}
