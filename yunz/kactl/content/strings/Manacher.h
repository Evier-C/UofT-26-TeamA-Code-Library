/**
 * Author: User adamant on CodeForces
 * Source: http://codeforces.com/blog/entry/12143
 * Description: 对串的每个位置求: p[0][i] = 以 i-1 和 i 之间为中心的最长偶回文的半长,
 *  p[1][i] = 以 i 为中心的最长奇回文的半长 (向下取整).
 * Usage: array<vi, 2> p = manacher(s); // p[0] 长 n+1, p[1] 长 n
 * Time: O(N)
 * Status: Stress-tested
 */
#pragma once

array<vi,2>manacher(const string&s){
	int n=sz(s);
	array<vi,2>p={vi(n+1),vi(n)};
	rep(z,0,2)for(int i=0,l=0,r=0;i<n;i++){
		int t=r-i+!z;
		if(i<r)p[z][i]=min(t,p[z][l+t]);
		int L=i-p[z][i],R=i+p[z][i]-!z;
		while(L>=1&&R+1<n&&s[L-1]==s[R+1])
			p[z][i]++,L--,R++;
		if(R>r)l=L,r=R;
	}
	return p;
}
