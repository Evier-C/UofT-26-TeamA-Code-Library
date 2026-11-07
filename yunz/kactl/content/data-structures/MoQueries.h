/**
 * Description: 普通莫队 Mo, 全局对象 mo: 离线回答 q 个区间询问 a[l..r], 要求能
 * $O(1)$ 地把一个数加入或移出当前区间, 并维护当前答案 cur.
 * 输入: mo.n, mo.q, mo.a[1..n]; 第 i 个询问存为 mo.qs[i] = \{l, r, i\},
 * 下标从 1 开始.
 * 你要改的地方: 结构体里的 add(i) 和 del(i), 把 a[i] 加入或移出当前区间并更新
 * cur, 需要的辅助数组也写成成员. 下面的 add, del 是例子: 区间不同值个数,
 * 要求 a 已离散化到 1..n.
 * solve() 之后 ans[i] 为第 i 个询问的答案, 顺序和输入一致.
 * 块长 $B = n / \sqrt q$, 奇数块按 r 升序, 偶数块按 r 降序, 减少 R 来回跑.
 * 注意: ans 和 cur 是 ll; solve 会打乱 qs 的顺序; 对象要定义在全局;
 * 多组数据清空 cnt 等自己维护的数组和 cur.
 * Usage: cin >> mo.n >> mo.q;
 * for (int i = 1; i <= mo.n; i++) cin >> mo.a[i]; // 先离散化
 * for (int i = 1; i <= mo.q; i++) {
 *   cin >> mo.qs[i].l >> mo.qs[i].r;
 *   mo.qs[i].id = i;
 * }
 * mo.solve();
 * for (int i = 1; i <= mo.q; i++) cout << mo.ans[i] << endl;
 * Time: $O(n \sqrt q)$ 次 add 和 del
 */
#pragma once

struct Mo{
	static const int N=2e5+5;
	struct Query{int l,r,id;};
	int n,q,B,a[N];
	Query qs[N];
	ll ans[N],cur;
	// ---- 按题意改: 辅助数组, add, del ----
	int cnt[N]; // 例子: 每个值的出现次数
	void add(int i){ // a[i] 进入当前区间
		if(cnt[a[i]]==0)cur++;
		cnt[a[i]]++;
	}
	void del(int i){ // a[i] 离开当前区间
		cnt[a[i]]--;
		if(cnt[a[i]]==0)cur--;
	}
	// ---- 以下不用改 ----
	void solve(){
		B=max(1,(int)(n/sqrt(q)));
		int b=B;
		sort(qs+1,qs+q+1,[b](const Query&x,const Query&y){
			if(x.l/b!=y.l/b)return x.l<y.l;
			if((x.l/b)&1)return x.r<y.r;
			return x.r>y.r;
		});
		int L=1,R=0; // 当前区间 [L, R], 开始为空
		for(int i=1;i<=q;i++){
			while(L>qs[i].l)add(--L);
			while(R<qs[i].r)add(++R);
			while(L<qs[i].l)del(L++);
			while(R>qs[i].r)del(R--);
			ans[qs[i].id]=cur;
		}
	}
}mo;
