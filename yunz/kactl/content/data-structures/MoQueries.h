/**
 * Description: 普通莫队, 离线回答 q 个区间询问 a[l..r]. 只需写 add(i), del(i):
 * 把 a[i] 加入或移出当前区间并维护答案 cur. 下面的 add, del 是例子:
 * 区间不同值个数, 值已离散化到 1..n, 按题意改.
 * 块长 $B = n / \sqrt q$, 奇偶块按 r 交替排序.
 * Usage: 读入 n, q, a[1..n]; 第 i 个询问 qs[i] = {l, r, i};
 * solve(); // 之后 ans[i] 为第 i 个询问的答案
 * 多组数据: 清空 cnt 和 cur
 * Time: $O(n \sqrt q)$ 次 add/del
 */
#pragma once

const int N=2e5+5;
int n,q,B,a[N];
struct Query{int l,r,id;}qs[N];
ll ans[N],cur;
int cnt[N];
void add(int i){if(cnt[a[i]]++==0)cur++;} // a[i] 进入
void del(int i){if(--cnt[a[i]]==0)cur--;} // a[i] 离开
bool cmp(const Query&x,const Query&y){
	if(x.l/B!=y.l/B)return x.l<y.l;
	return (x.l/B)&1?x.r<y.r:x.r>y.r;
}
void solve(){
	B=max(1,(int)(n/sqrt(q)));
	sort(qs+1,qs+q+1,cmp);
	int L=1,R=0; // 当前区间 [L, R], 开始为空
	for(int i=1;i<=q;i++){
		while(L>qs[i].l)add(--L);
		while(R<qs[i].r)add(++R);
		while(L<qs[i].l)del(L++);
		while(R>qs[i].r)del(R--);
		ans[qs[i].id]=cur;
	}
}
