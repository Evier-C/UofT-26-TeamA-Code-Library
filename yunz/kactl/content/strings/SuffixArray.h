/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: 构建字符串的后缀数组.
 * \texttt{sa[i]} 是排序后第 $i$ 个后缀的起始下标.
 * 返回的数组长 $n+1$, 且 \texttt{sa[0] = n}.
 * \texttt{lcp} 数组存后缀数组中相邻后缀的最长公共前缀:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * 输入串不能含字符 0.
 * Usage: SuffixArray S(s); S.sa[i]; S.lcp[i];
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

struct SuffixArray{
	vi sa,lcp;
	SuffixArray(string s,int lim=256){ // 或 vector<int>
		s.push_back(0);int n=sz(s),k=0,a,b;
		vi x(all(s)),y(n),ws(max(n,lim));
		sa=lcp=y,iota(all(sa),0);
		for(int j=0,p=0;p<n;j=max(1,j*2),lim=p){
			p=j,iota(all(y),n-j);
			rep(i,0,n)if(sa[i]>=j)y[p++]=sa[i]-j;
			fill(all(ws),0);
			rep(i,0,n)ws[x[i]]++;
			rep(i,1,lim)ws[i]+=ws[i-1];
			for(int i=n;i--;)sa[--ws[x[y[i]]]]=y[i];
			swap(x,y),p=1,x[sa[0]]=0;
			rep(i,1,n)a=sa[i-1],b=sa[i],x[b]=
				(y[a]==y[b]&&y[a+j]==y[b+j])?p-1:p++;
		}
		for(int i=0,j;i<n-1;lcp[x[i++]]=k)
			for(k&&k--,j=sa[x[i]-1];
					s[i+k]==s[j+k];k++);
	}
};
