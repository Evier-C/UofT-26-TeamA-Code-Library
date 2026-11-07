/**
 * Description: 后缀自动机 SAM. 字符集为小写字母, 字符以 0..25 传入. 根为 1, 状态数至多 2n-1.
 * 每个状态 v 表示一组 endpos 相同的子串: len[v] 为其中最长串的长度,
 * fa[v] 为后缀链接, ch[v][c] 为转移, 0 表示没有转移.
 * extend(c) 在串末尾加入字符 c. calc() 需在全部 extend 之后调用:
 * 按 len 计数排序得到拓扑序 ord[1..tot], 逆序把 siz 累加到 fa,
 * 使 siz[v] 等于 v 的 endpos 大小, 即 v 中每个串在原串中的出现次数;
 * 返回本质不同子串个数 $\sum_{v>1} len_v-len_{fa_v}$.
 * 查询 t 的出现次数: 从根沿 ch 走 t, 走不动则为 0, 否则为终点的 siz.
 * 空间: ch 为 $2N \times 26$ 个 int, N 取 5e5 时约 104MB, 字符集或 N 大时注意.
 * 多组数据先 init(), 它只清空用过的状态.
 * Usage: scanf("\%s",s+1);
 * int n=strlen(s+1);
 * init(); // 每组数据先清空
 * for(int i=1;i<=n;i++)extend(s[i]-'a');
 * ll d=calc(); // 本质不同子串数, 并求出 siz
 * // 查询 t[1..m] 的出现次数
 * int u=1;
 * for(int i=1;i<=m\&\&u;i++)u=ch[u][t[i]-'a'];
 * int occ=u?siz[u]:0;
 * Time: O(26n)
 * Memory: O(26n)
 */
#pragma once

const int N=5e5+5; // 串长上限
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
