/**
 * Description: AC 自动机, 多模式串匹配. 字符集为小写字母, 串均为 1-indexed. 根为 0.
 * insert(s,n,id) 把第 id 个模式串 s[1..n] 插入 Trie, pos[id] 记下它结尾的节点.
 * build() 用 BFS 求 fail, 并把缺失的转移补成 tr[fail[u]][c], 得到 Trie 图;
 * q[1..tot] 为 BFS 序.
 * query(t,m) 在文本 t[1..m] 上跑自动机, 在每个经过的节点 cnt++, 再按 BFS 逆序沿 fail 树累加.
 * 之后节点 v 的 cnt 即以 v 代表的串在 t 中的出现次数, 第 id 个模式串出现 cnt[pos[id]] 次.
 * 允许重复模式串, 它们共享节点; 不允许空串.
 * N 为模式串总长上限; tr 为 $26N$ 个 int, N 取 1e6 时约 104MB.
 * 多组数据先 init(), 它只清空用过的节点. 同一自动机换文本再 query 前, 要把 cnt[0..tot] 清 0.
 * Usage: init(); // 每组数据先清空
 * for(int i=1;i<=k;i++){
 *   scanf("\%s",p+1);
 *   insert(p,strlen(p+1),i);
 * }
 * build();
 * scanf("\%s",t+1);
 * query(t,strlen(t+1));
 * for(int i=1;i<=k;i++)printf("\%d ",cnt[pos[i]]);
 * Time: 构建 O(26L), L 为模式串总长; 查询 O(m+L)
 */
#pragma once

const int N=1e6+5; // 模式串总长上限
int tr[N][26],fail[N],cnt[N],q[N],tot;
int pos[N]; // pos[id]: 第 id 个模式串结尾的节点
void init(){
	for(int i=0;i<=tot;i++){
		memset(tr[i],0,sizeof tr[i]);
		fail[i]=0;
		cnt[i]=0;
	}
	tot=0;
}
void insert(char*s,int n,int id){
	int u=0;
	for(int i=1;i<=n;i++){
		int c=s[i]-'a';
		if(!tr[u][c])tr[u][c]=++tot;
		u=tr[u][c];
	}
	pos[id]=u;
}
void build(){
	int hd=1,tl=0;
	for(int c=0;c<26;c++){
		if(tr[0][c])q[++tl]=tr[0][c];
	}
	while(hd<=tl){
		int u=q[hd++];
		for(int c=0;c<26;c++){
			int v=tr[u][c];
			if(v){
				fail[v]=tr[fail[u]][c];
				q[++tl]=v;
			}else{
				tr[u][c]=tr[fail[u]][c];
			}
		}
	}
}
void query(char*t,int m){
	int u=0;
	for(int i=1;i<=m;i++){
		u=tr[u][t[i]-'a'];
		cnt[u]++;
	}
	// q[1..tot] 为 BFS 序, 逆序累加到 fail
	for(int i=tot;i>=1;i--)cnt[fail[q[i]]]+=cnt[q[i]];
}
