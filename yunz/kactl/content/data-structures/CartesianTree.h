/**
 * Description: 笛卡尔树: 对序列 a[1..n] 建二叉树, 下标满足二叉搜索树性质,
 * 即中序遍历为 1, 2, ..., n; 值满足堆性质. 默认小根: 根是最小值.
 * 改大根: 把 build 里 while 的 a[stk[top]]>a[i] 改成 a[stk[top]]<a[i].
 * 相等: 靠左的相等元素是祖先, 靠右的在它的右子树里.
 * 输入: 全局 n 和 a[1..n], 要求 n 至少为 1. build() 用单调栈 $O(n)$ 建树, 得到:
 * root 为根; ls[i], rs[i] 为左右儿子, 0 表示没有;
 * i 的子树恰好是下标区间 [L[i], R[i]], 也就是 a[i] 作为最小值能向两边
 * 延伸的最大区间: 左边停在第一个不大于 a[i] 的位置, 右边停在第一个
 * 严格小于 a[i] 的位置.
 * 性质: [l, r] 最小值的位置, 相等取最左, 等于 l 和 r 在树上的 LCA.
 * 常见用法: 以 a[i] 为最小值的子数组个数为 (i - L[i] + 1) * (R[i] - i + 1),
 * 每个子数组恰好算一次, 最小值相等时算给最左的;
 * 直方图最大矩形为 a[i] * (R[i] - L[i] + 1) 的最大值;
 * 已排好序的键配随机优先级, 以优先级为 a 建树, 就是 $O(n)$ 建 treap.
 * 注意: 多组数据直接重新 build, 会覆盖 ls, rs, L, R.
 * Usage: cin >> n;
 * for (int i = 1; i <= n; i++) cin >> a[i];
 * build();
 * int rt = root; // 最小值的位置, 有多个时取最左
 * ll s = 0; // 所有子数组的最小值之和
 * for (int i = 1; i <= n; i++)
 *   s += a[i] * (i - L[i] + 1) * (R[i] - i + 1);
 * Time: O(N)
 */
#pragma once

const int N=2e5+5;
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
