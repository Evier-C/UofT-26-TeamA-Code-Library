/**
 * Description: 后缀自动机, 小写字母. 根为 1, 状态数至多 2n-1.
 * 串长上限 SAM::N, ch 约 $52N$ 个 int, N 取 5e5 时约 104MB; 对象必须开在全局.
 * Usage: char s[SAM::N],t[SAM::N]; // 全局, 从 1 开始
 * SAM sam2; // 第二个实例也开在全局
 * scanf("\%s",s+1);
 * int n=strlen(s+1);
 * sam.init(); // 每组数据先清空, 新对象可省
 * for(int i=1;i<=n;i++)sam.extend(s[i]-'a');
 * // 状态 v: sam.len[v] 为最长串长, sam.fa[v] 为
 * // 后缀链接, sam.ch[v][c] 为转移, 0 表示无
 * // 全部 extend 之后调用, 返回本质不同子串数
 * ll d=sam.calc();
 * // 同时求出 sam.siz[v]: v 中每个串的出现次数
 * // t[1..m] 在 s 中的出现次数
 * int u=1;
 * for(int i=1;i<=m\&\&u;i++)u=sam.ch[u][t[i]-'a'];
 * int occ=u?sam.siz[u]:0;
 * Time: O(26n)
 * Memory: O(26n)
 */
#pragma once

struct SAM{
	static const int N=5e5+5; // 串长上限
	int len[N*2],fa[N*2],ch[N*2][26],siz[N*2];
	int tot=1,last=1;
	int buc[N],ord[N*2];
	void init(){
		for(int i=1;i<=tot;i++){
			len[i]=0;
			fa[i]=0;
			siz[i]=0;
			memset(ch[i],0,sizeof ch[i]);
		}
		tot=1;
		last=1;
	}
	void extend(int c){
		int p=last;
		int cur=++tot;
		len[cur]=len[p]+1;
		siz[cur]=1;
		for(;p&&!ch[p][c];p=fa[p])ch[p][c]=cur;
		if(!p){
			fa[cur]=1;
		}else{
			int q=ch[p][c];
			if(len[q]==len[p]+1){
				fa[cur]=q;
			}else{
				int cl=++tot; // 复制 q, 其 siz 为 0
				len[cl]=len[p]+1;
				fa[cl]=fa[q];
				memcpy(ch[cl],ch[q],sizeof ch[q]);
				for(;p&&ch[p][c]==q;p=fa[p])ch[p][c]=cl;
				fa[q]=cl;
				fa[cur]=cl;
			}
		}
		last=cur;
	}
	ll calc(){
		int n=len[last];
		for(int i=0;i<=n;i++)buc[i]=0;
		for(int i=1;i<=tot;i++)buc[len[i]]++;
		for(int i=1;i<=n;i++)buc[i]+=buc[i-1];
		for(int i=tot;i>=1;i--)ord[buc[len[i]]--]=i;
		ll res=0;
		for(int i=tot;i>=2;i--){ // ord[1] 为根
			int v=ord[i];
			siz[fa[v]]+=siz[v];
			res+=len[v]-len[fa[v]];
		}
		return res;
	}
}sam;
