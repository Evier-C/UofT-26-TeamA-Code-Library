/**
 * Description: 虚树 (单调栈建法). 需要原树 (根为 1) 的 dfs 序 dfn[]
 * 和 lca(x,y), 由别的模板提供. 给定 $k$ 个互不相同的关键点 h[1..k],
 * 建出包含关键点, 两两 LCA 和根 1 的虚树, 点数不超过 $2k$.
 * vt[u] 为虚树中 $u$ 的儿子 (父到子), 虚树边 $(u, v)$ 代表原树一条链,
 * 长度为 dep[v]-dep[u]. 用到的虚树点为 vs[1..vn], 根 1 不一定是关键点
 * (自己用数组标记关键点). 每次 build 会重新清空用到的 vt.
 * Usage: // 每次询问:
 * for(int i=1;i<=k;i++) cin>>h[i],key[h[i]]=1;
 * build(h,k); dp(1); // 在 vt 上 DP
 * for(int i=1;i<=k;i++) key[h[i]]=0; // 清空标记
 * Time: O(k \log k) 次 lca
 */
#pragma once

const int N=2e5+5;
extern int dfn[];int lca(int x,int y); // 用户提供
vector<int>vt[N];
int stk[N],tp,vs[N],vn;
bool cmp(int x,int y){return dfn[x]<dfn[y];}
void push(int x){vt[x].clear(),vs[++vn]=x,stk[++tp]=x;}
void build(int*h,int k){
	sort(h+1,h+k+1,cmp);
	tp=vn=0,push(1);
	for(int i=1;i<=k;i++)if(h[i]!=1){
		int l=lca(h[i],stk[tp]);
		if(l!=stk[tp]){
			// 栈顶不在 h[i] 到根的链上, 弹出并连边
			while(dfn[l]<dfn[stk[tp-1]])
				vt[stk[tp-1]].push_back(stk[tp]),tp--;
			if(l!=stk[tp-1]){
				int x=stk[tp--];
				push(l),vt[l].push_back(x);
			}else vt[l].push_back(stk[tp--]);
		}
		push(h[i]);
	}
	for(int i=1;i<tp;i++)vt[stk[i]].push_back(stk[i+1]);
}
