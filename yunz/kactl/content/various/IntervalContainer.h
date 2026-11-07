/**
 * Description: 用 set 维护互不相交的整数闭区间, 相交或相邻的自动合并.
 * 要求 $l \le r$, 端点不要用 INT\_MIN 或 INT\_MAX. 左闭右开 $[L, R)$ 时调用 add(L, R - 1).
 * Usage: add(1, 5); add(7, 9); add(6, 6); // st = {[1, 9]}
 * del(3, 4); // st = {[1, 2], [5, 9]}, tot = 7
 * auto it = getIt(6); // it 指向 (5, 9)
 * if(getIt(x) == st.end()) ...; // x 没被覆盖
 * for(auto [l, r] : st) ...; // 按顺序遍历所有区间
 * st.clear(); tot = 0; // 多组数据清空
 * Time: 每次操作均摊 O(\log n)
 */
#pragma once

set<pair<int,int>>st;
ll tot; // 被覆盖的点数
void add(int l,int r){
	auto it=st.lower_bound({l,INT_MIN});
	if(it!=st.begin()&&prev(it)->second>=l-1)it--;
	while(it!=st.end()&&it->first<=r+1){ // 相交或相邻
		l=min(l,it->first);
		r=max(r,it->second);
		tot-=it->second-it->first+1;
		it=st.erase(it);
	}
	st.insert({l,r});
	tot+=r-l+1;
}
void del(int l,int r){
	auto it=st.lower_bound({l,INT_MIN});
	if(it!=st.begin()&&prev(it)->second>=l)it--;
	while(it!=st.end()&&it->first<=r){
		int L=it->first,R=it->second;
		it=st.erase(it);
		tot-=R-L+1;
		if(L<l){ // 左边剩下 [L, l - 1]
			st.insert({L,l-1});
			tot+=l-L;
		}
		if(R>r){ // 右边剩下 [r + 1, R]
			st.insert({r+1,R});
			tot+=R-r;
		}
	}
}
set<pair<int,int>>::iterator getIt(int x){
	auto it=st.upper_bound({x,INT_MAX});
	if(it==st.begin())return st.end();
	it--;
	if(it->second<x)return st.end();
	return it;
}
