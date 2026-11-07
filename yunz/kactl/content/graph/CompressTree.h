/**
 * Description: 虚树 (单调栈建法). 多次询问, 每次给出 $k$ 个关键点, 总和
 * 不大时, 只保留关键点, 它们两两的 LCA 和根 1, 建一棵点数不超过 $2k$
 * 的虚树, 在上面做树形 DP. 结构体 VTree, 全局对象 VT.
 * 需要用户在结构体外提供 (本文件只声明): 原树 (根为 1) 的全局 dfs 序
 * 数组 int dfn[] 和函数 int lca(int x,int y). 若用 HLD 结构体 H:
 * 把 H.dfn 复制到全局 dfn, lca 写成 return H.lca(x,y).
 * build(h,k): h[1..k] 为互不相同的关键点 (会被按 dfn 排序).
 * 结果: vt[u] 为虚树中 $u$ 的儿子 (父到子), 虚树边 $(u, v)$ 代表原树中
 * 一条链, 长度为 dep[v]$-$dep[u]. 用到的虚树点为 vs[1..vn], 根 1
 * 总在虚树中但不一定是关键点 (自己用数组标记关键点).
 * 每次 build 会清空用到的点的 vt, 不需要全局清空.
 * 对象很大, 必须是全局 (或 static) 变量; 第二个: 全局写 VTree VT2;
 * Usage: int dfn[N]; int lca(int x,int y){...} // 用户提供
 * // 每次询问:
 * cin>>k;
 * for(int i=1;i<=k;i++){
 *   cin>>h[i];
 *   key[h[i]]=1;
 * }
 * VT.build(h,k);
 * dp(1); // 在 VT.vt 上做 DP, 点集为 VT.vs[1..VT.vn]
 * for(int i=1;i<=k;i++) key[h[i]]=0; // 清空标记
 * Time: O(k \log k) 加 O(k) 次 lca
 */
#pragma once

extern int dfn[]; // 用户提供
int lca(int x,int y); // 用户提供
struct VTree{
	static const int N=2e5+5;
	vector<int>vt[N];
	int stk[N],tp,vs[N],vn;
	static bool cmp(int x,int y){return dfn[x]<dfn[y];}
	void push(int x){ // 新点入栈
		vt[x].clear();
		vs[++vn]=x;
		stk[++tp]=x;
	}
	void build(int*h,int k){
		sort(h+1,h+k+1,cmp);
		tp=vn=0;
		push(1);
		for(int i=1;i<=k;i++){
			if(h[i]==1)continue;
			int l=lca(h[i],stk[tp]);
			if(l!=stk[tp]){
				// 栈顶不在 h[i] 到根的链上, 弹出并连边
				while(dfn[l]<dfn[stk[tp-1]]){
					vt[stk[tp-1]].push_back(stk[tp]);
					tp--;
				}
				int x=stk[tp--];
				if(l!=stk[tp])push(l);
				vt[l].push_back(x);
			}
			push(h[i]);
		}
		for(int i=1;i<tp;i++)vt[stk[i]].push_back(stk[i+1]);
	}
}VT;
