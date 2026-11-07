/**
 * Author: chilli
 * License: CC0
 * Description: z[i] 为 s[i:] 与 s 的最长公共前缀长度, 但 z[0] = 0. (abacaba 得 0010301)
 * Usage: vi z = Z(s);
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vi Z(const string&S){
	vi z(sz(S));
	int l=-1,r=-1;
	rep(i,1,sz(S)){
		z[i]=i>=r?0:min(r-i,z[i-l]);
		while(i+z[i]<sz(S)&&S[i+z[i]]==S[z[i]])
			z[i]++;
		if(i+z[i]>r)
			l=i,r=i+z[i];
	}
	return z;
}
