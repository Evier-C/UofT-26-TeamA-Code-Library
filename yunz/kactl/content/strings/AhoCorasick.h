/**
 * Description: AC 自动机, 统计每个模式串在文本中的出现次数. 小写字母, 允许重复模式串, 不允许空串.
 * 模式串总长上限 AC::N, tr 约 $26N$ 个 int, N 取 1e6 时约 104MB; 对象必须开在全局.
 * Usage: char p[AC::N],t[AC::N]; // 全局, 从 1 开始
 * AC ac2; // 第二个实例也开在全局
 * ac.init(); // 每组数据先清空, 新对象可省
 * for(int i=1;i<=k;i++){
 *   scanf("\%s",p+1);
 *   ac.insert(p,strlen(p+1),i); // 第 i 个模式串
 * }
 * ac.build();
 * scanf("\%s",t+1);
 * ac.query(t,strlen(t+1));
 * // 第 i 个模式串在 t 中的出现次数
 * for(int i=1;i<=k;i++)
 *   printf("\%d ",ac.cnt[ac.pos[i]]);
 * // 换一个文本再 query 前, 先清空 cnt
 * for(int i=0;i<=ac.tot;i++)ac.cnt[i]=0;
 * Time: 构建 O(26L), L 为模式串总长; 查询 O(m+L)
 */
#pragma once

struct AC{
	static const int N=1e6+5; // 模式串总长上限
	int tr[N][26],fail[N],cnt[N],q[N],tot=0;
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
}ac;
