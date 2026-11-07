/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: AC 自动机 (Aho-Corasick), 用于多模式串匹配. 起始节点下标为 0.
 * 默认字母表为大写字母, 按需修改 alpha 和 first.
 * find(word) 对每个位置返回在该处结尾的最长模式串的下标, 没有则为 -1.
 * findAll($-$, word) 对每个位置找出从该处开始的所有模式串 (短的在前;
 * 若无重复模式串, 总数至多 $N \sqrt N$).
 * 允许重复模式串, 不允许空串. 要求从每个位置开始的最长模式串, 就把输入全部反转.
 * 字母表很大时, 把每个符号拆成若干块, 并用哨兵位标记符号边界.
 * Usage: AhoCorasick ac(pat); // pat 为 vector<string>
 * vi r = ac.find(word); vector<vi> res = ac.findAll(pat, word);
 * Time: 构建 $O(26N)$, 其中 $N =$ 模式串总长. find(x) 为 $O(N)$,
 * 其中 N = x 的长度. findAll 为 $O(NM)$.
 * Status: stress-tested
 */
#pragma once

struct AhoCorasick{
	enum{alpha=26,first='A'}; // 按需修改!
	struct Node{
		// (nmatches 可选)
		int back,next[alpha],start=-1,end=-1,nmatches=0;
		Node(int v){memset(next,v,sizeof(next));}
	};
	vector<Node>N;
	vi backp;
	void insert(string&s,int j){
		assert(!s.empty());
		int n=0;
		for(char c:s){
			int&m=N[n].next[c-first];
			if(m==-1){n=m=sz(N);N.emplace_back(-1);}
			else n=m;
		}
		if(N[n].end==-1)N[n].start=j;
		backp.push_back(N[n].end);
		N[n].end=j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string>&pat):N(1,-1){
		rep(i,0,sz(pat))insert(pat[i],i);
		N[0].back=sz(N);
		N.emplace_back(0);

		queue<int>q;
		for(q.push(0);!q.empty();q.pop()){
			int n=q.front(),prev=N[n].back;
			rep(i,0,alpha){
				int&ed=N[n].next[i],y=N[prev].next[i];
				if(ed==-1)ed=y;
				else{
					N[ed].back=y;
					(N[ed].end==-1?N[ed].end:backp[N[ed].start])
						=N[y].end;
					N[ed].nmatches+=N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	vi find(string word){
		int n=0;
		vi res; // ll count = 0;
		for(char c:word){
			n=N[n].next[c-first];
			res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
		return res;
	}
	vector<vi>findAll(vector<string>&pat,string word){
		vi r=find(word);
		vector<vi>res(sz(word));
		rep(i,0,sz(word)){
			int ind=r[i];
			while(ind!=-1){
				res[i-sz(pat[ind])+1].push_back(ind);
				ind=backp[ind];
			}
		}
		return res;
	}
};
