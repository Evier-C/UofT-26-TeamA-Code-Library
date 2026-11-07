/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: 求最长严格上升子序列，返回其各元素的下标。
 * Usage: vi idx = lis(S); // S 为 vector, 返回递增的下标序列
 * Time: $O(N \log N)$
 * Status: Tested on kattis:longincsubseq, stress-tested
 */
#pragma once

template<class I>vi lis(const vector<I>&S){
	if(S.empty())return {};
	vi prev(sz(S));
	typedef pair<I,int>p;
	vector<p>res;
	rep(i,0,sz(S)){
		// 求最长不降子序列时把 0 改为 i
		auto it=lower_bound(all(res),p{S[i],0});
		if(it==res.end())res.emplace_back(),it=res.end()-1;
		*it={S[i],i};
		prev[i]=it==res.begin()?0:(it-1)->second;
	}
	int L=sz(res),cur=res.back().second;
	vi ans(L);
	while(L--)ans[L]=cur,cur=prev[cur];
	return ans;
}