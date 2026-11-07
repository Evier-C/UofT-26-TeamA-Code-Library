/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: 可撤销并查集 (按大小合并, 无路径压缩).
 * 不需要撤销时可去掉 st, time() 和 rollback().
 * Usage: RollbackUF uf(n); uf.join(a, b); uf.find(x); uf.size(x);
 * int t = uf.time(); ...; uf.rollback(t);
 * Time: $O(\log(N))$
 * Status: tested as part of DirectedMST.h
 */
#pragma once

struct RollbackUF{
	vi e;vector<pii>st;
	RollbackUF(int n):e(n,-1){}
	int size(int x){return -e[find(x)];}
	int find(int x){return e[x]<0?x:find(e[x]);}
	int time(){return sz(st);}
	void rollback(int t){
		for(int i=time();i-->t;)
			e[st[i].first]=st[i].second;
		st.resize(t);
	}
	bool join(int a,int b){
		a=find(a),b=find(b);
		if(a==b)return false;
		if(e[a]>e[b])swap(a,b);
		st.push_back({a,e[a]});
		st.push_back({b,e[b]});
		e[a]+=e[b];e[b]=a;
		return true;
	}
};
