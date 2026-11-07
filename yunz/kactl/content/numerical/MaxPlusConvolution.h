/**
 * Description: $(\max,+)$ 卷积: 给定 $a_0..a_{n-1}$ (任意) 和 $b_0..b_{m-1}$ (凹, 即差分
 * $b_{j+1}-b_j$ 不增), 求 $c_k = \max_{i+j=k} (a_i + b_j)$, $k = 0..n+m-2$.
 * 一般的 $(\max,+)$ 卷积只能 $O(nm)$; $b$ 凹时最优决策单调, 可以分治.
 * \textbf{决策单调}: 对 $k$, 合法的 $i$ 满足 $\max(0, k-m+1) \le i \le \min(k, n-1)$;
 * 记 $opt(k)$ 为取到最大值的 $i$ (有多个时取最小的). 设 $k < k'$, $i < i'$,
 * 下标 $k-i' < k-i, k'-i' < k'-i$ 且两边和相等, 由凹性
 * $b_{k-i'} + b_{k'-i} \le b_{k-i} + b_{k'-i'}$, 所以
 * $(a_{i'}+b_{k'-i'}) - (a_i+b_{k'-i}) \ge (a_{i'}+b_{k-i'}) - (a_i+b_{k-i})$:
 * 若 $i'$ 在 $k$ 处严格优于 $i$, 则在 $k'$ 处也严格优于 $i$. 故 $opt(k)$ 随 $k$ 不降.
 * \textbf{分治}: mpdc(l, r, optl, optr) 求 $c_l..c_r$, 已知它们的 $opt$ 都在 $[optl, optr]$.
 * 取 $mid = (l+r)/2$, 在 $[optl, optr]$ 与合法范围的交里扫 $i$ 求 $c_{mid}$ 和 $opt(mid)$
 * (严格大于才更新, 即取最小的 $i$), 再递归 mpdc(l, mid-1, optl, opt) 和
 * mpdc(mid+1, r, opt, optr). 每层总扫描量 $O(n+m)$, 共 $O(\log)$ 层.
 * 若凹的是 $a$, 交换两个参数即可. 求 $(\min,+)$ 卷积要求 $b$ 凸, 全部取负即可.
 * \textbf{两个都凹}时更简单, $O(n+m)$: $c_0 = a_0 + b_0$, 把两者的差分数组按从大到小
 * 归并 (同闵可夫斯基和), 依次累加得到 $c_1, c_2, \dots$.
 * Usage: vector<ll> a={1,5,2},b={0,3,4}; // b 凹, a, b 非空
 * vector<ll> c=maxPlus(a,b); // c={1,5,8,9,6}
 * Time: O((n+m) \log (n+m))
 */
#pragma once

vector<ll>va,vb,vc;
// 求 c[l..r], 已知最优的 i 在 [optl, optr] 中
void mpdc(int l,int r,int optl,int optr){
	if(l>r)
		return;
	int mid=(l+r)/2;
	int best=-1;
	int lo=max(optl,mid-(int)vb.size()+1); // 合法的 i 范围
	int hi=min({optr,mid,(int)va.size()-1});
	for(int i=lo;i<=hi;i++){ // 取最左的最优 i
		ll v=va[i]+vb[mid-i];
		if(best==-1||v>vc[mid]){
			vc[mid]=v;
			best=i;
		}
	}
	mpdc(l,mid-1,optl,best);
	mpdc(mid+1,r,best,optr);
}
vector<ll>maxPlus(const vector<ll>&a,const vector<ll>&b){
	va=a;
	vb=b;
	vc.assign(a.size()+b.size()-1,0);
	mpdc(0,(int)vc.size()-1,0,(int)a.size()-1);
	return vc;
}
