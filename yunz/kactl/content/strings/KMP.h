/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[x] 为 s 的最长前缀中以 x 结尾者的长度, 不算 s[0...x] 本身
 * (即 s[0...x] 的最长真 border; abacaba 得 0010123).
 * match 找出 pat 在 s 中的所有出现位置.
 * Usage: vi p = pi(s);
 * vi occ = match(s, pat); // 每次出现的起始下标
 * Time: O(n)
 * Status: Tested on kattis:stringmatching
 */
#pragma once

vi pi(const string&s){
	vi p(sz(s));
	rep(i,1,sz(s)){
		int g=p[i-1];
		while(g&&s[i]!=s[g])g=p[g-1];
		p[i]=g+(s[i]==s[g]);
	}
	return p;
}

vi match(const string&s,const string&pat){
	vi p=pi(pat+'\0'+s),res;
	rep(i,sz(p)-sz(s),sz(p))
		if(p[i]==sz(pat))res.push_back(i-2*sz(pat));
	return res;
}
