/**
 * Description: 小根笛卡尔树, 相等时靠左的是祖先. n 至少为 1. 改大根: build 里
 * a[stk[top]]>a[i] 改成小于号. i 的子树为 [L[i], R[i]], 即 a[i] 作为最小值
 * 的最大区间, 左边遇到不大于, 右边遇到小于就停. [l, r] 最小值的位置
 * 等于 l, r 的 LCA. 对象要定义在全局.
 * Usage: cin >> ct.n;
 * for (int i = 1; i <= ct.n; i++) cin >> ct.a[i];
 * ct.build(); // 多组数据直接重新 build
 * int rt = ct.root; // 最小值的位置, 有多个时取最左
 * int x = ct.ls[i], y = ct.rs[i]; // 儿子, 0 表示没有
 * // 所有子数组的最小值之和, 每个子数组只算一次
 * ll s = 0;
 * for (int i = 1; i <= ct.n; i++)
 *   s += ct.a[i] * (i - ct.L[i] + 1) * (ct.R[i] - i + 1);
 * // 直方图最大矩形: a[i] * (R[i] - L[i] + 1) 的最大值
 * Time: O(N)
 */
#pragma once

struct CartesianTree{
	static const int N=2e5+5;
	int n,root;
	ll a[N];
	int ls[N],rs[N],L[N],R[N];
	int stk[N];
	void build(){
		int top=0;
		for(int i=1;i<=n;i++){
			ls[i]=0;
			rs[i]=0;
			int last=0; // 最后弹出的点, 成为 i 的左儿子
			while(top&&a[stk[top]]>a[i]){
				R[stk[top]]=i-1;
				last=stk[top];
				top--;
			}
			ls[i]=last;
			if(top)rs[stk[top]]=i;
			L[i]=top?stk[top]+1:1;
			stk[++top]=i;
		}
		for(int j=1;j<=top;j++)R[stk[j]]=n;
		root=stk[1];
	}
}ct;
