/**
 * Description: 后缀自动机 (SAM). 根为 1, 节点数至多 2n-1.
 * len[v] 为状态 v 中最长串的长度, fa[v] 为后缀链接, ch[v][c] 为转移.
 * siz[v] 为 v 的 endpos 集合大小, 即 v 中每个串的出现次数 (calc 后有效).
 * calc 按 len 计数排序得到拓扑序 ord, 逆序把 siz 累加到 fa,
 * 并返回本质不同子串个数 $\sum_{v>1} len_v-len_{fa_v}$.
 * Usage: init(); // 多组数据先清空
 * for(int i=1;i<=n;i++)extend(s[i]-'a');
 * ll d=calc(); // 本质不同子串数, 同时求出 siz
 * // t 的出现次数: 从 1 沿 ch 走 t, 走不动为 0, 否则为 siz[u]
 * Time: O(n \Sigma)
 * Memory: O(n \Sigma)
 */
#pragma once

const int N=5e5+5; // 串长上限
int len[N*2],fa[N*2],ch[N*2][26],siz[N*2],tot=1,last=1;
int buc[N],ord[N*2];
void init(){
	for(int i=1;i<=tot;i++)
		len[i]=fa[i]=siz[i]=0,memset(ch[i],0,sizeof ch[i]);
	tot=last=1;
}
void extend(int c){
	int p=last,cur=++tot;
	len[cur]=len[p]+1;siz[cur]=1;
	for(;p&&!ch[p][c];p=fa[p])ch[p][c]=cur;
	if(!p)fa[cur]=1;
	else{
		int q=ch[p][c];
		if(len[q]==len[p]+1)fa[cur]=q;
		else{
			int cl=++tot; // 复制 q, 其 siz 为 0
			len[cl]=len[p]+1;fa[cl]=fa[q];
			memcpy(ch[cl],ch[q],sizeof ch[q]);
			for(;p&&ch[p][c]==q;p=fa[p])ch[p][c]=cl;
			fa[q]=fa[cur]=cl;
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
