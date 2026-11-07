/**
 * Description: 虚树: 关键点, 它们两两的 LCA 和根 1 (点数不超过 $2k$).
 * 用户在结构体外提供原树 (根为 1) 的全局 dfn[] 和 lca(x,y).
 * 对象必须是全局变量.
 * Usage: int dfn[N]; // 用户提供: 原树 dfs 序
 * int lca(int x,int y){...} // 用户提供
 * // 用 HLD 结构体 H 时: dfn 复制 H.dfn, lca 返回 H.lca(x,y)
 * // 每次询问:
 * cin>>k;
 * for(int i=1;i<=k;i++){
 *   cin>>h[i]; // 互不相同, build 会按 dfn 排序
 *   key[h[i]]=1; // 根 1 不一定是关键点
 * }
 * VT.build(h,k); // 自动清空用到的点的 vt
 * // VT.vt[u]: 虚树中 u 的儿子; 点集 VT.vs[1..VT.vn]
 * dp(1); // 在 VT.vt 上做 DP
 * for(int i=1;i<=k;i++) key[h[i]]=0; // 清空标记
 * VTree VT2; // 第二个对象 (全局)
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
