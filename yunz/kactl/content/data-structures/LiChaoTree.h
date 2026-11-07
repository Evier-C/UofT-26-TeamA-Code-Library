/**
 * Description: 李超树 LiChao, 全局对象 lc: 维护一堆直线或线段,
 * 查询某个整数 x 处的最大 y 值. x 取值于 [lo, hi), 动态开点,
 * 范围大如 $\pm 10^9$ 也不用离散化.
 * init(lo, hi): 设定 x 的范围并清空, 每组数据调用一次.
 * addLine(\{k, b\}): 插入直线 $y = kx + b$, 对所有 x 生效.
 * addSeg(\{k, b\}, x1, x2): 插入只在 $x \in [x_1, x_2)$ 上存在的线段, 左闭右开,
 * 超出 [lo, hi) 的部分自动忽略.
 * query(x): 返回所有覆盖 x 的线中 $kx + b$ 的最大值, 没有则返回 LLONG\_MIN.
 * 求最小值: 插入 $(-k, -b)$, 再把 query 的答案取负.
 * 注意: 要求 $|kx + b| < 9 \cdot 10^{18}$, $hi - lo < 9 \cdot 10^{18}$;
 * 节点数 M: 每条直线最多 1 个, 每条线段最多约 2 log C 个, C = hi - lo.
 * 默认 M = 4e6, 约 100MB; 只有直线时 M 取直线条数即可.
 * 对象必须是全局变量; 要第二棵就在全局再写 LiChao lc2;
 * Usage: lc.init(-1e9, 1e9 + 1); // x 的范围 [-1e9, 1e9]
 * lc.addLine({2, 3}); // y = 2x + 3
 * lc.addSeg({-1, 10}, 0, 5); // y = -x + 10, 只在 x = 0..4 上
 * ll y = lc.query(x); // 若为 LLONG_MIN 表示没有线覆盖 x
 * // 求最小: lc.addLine({-k, -b}); ll mn = -lc.query(x);
 * Time: 直线和查询 $O(\log C)$, 线段 $O(\log^2 C)$
 */
#pragma once

struct LiChao{
	static const int M=4e6+5; // 节点数
	struct Line{ll k,b;};
	Line ln[M];
	int ls[M],rs[M],tot,root;
	bool has[M]; // has: 节点上有线
	ll lo,hi;
	ll calc(Line a,ll x){return a.k*x+a.b;}
	void init(ll L,ll R){
		lo=L;
		hi=R;
		tot=0;
		root=0;
	}
	// 节点 p 管 [l, r), 在 [x, y) 上插入 a
	void ins(int&p,ll l,ll r,ll x,ll y,Line a){
		if(y<=l||r<=x)return;
		if(!p){ // 新建节点
			p=++tot;
			ls[p]=0;
			rs[p]=0;
			has[p]=0;
		}
		ll m=l+(r-l)/2;
		if(x<=l&&r<=y){
			if(!has[p]){
				ln[p]=a;
				has[p]=1;
				return;
			}
			if(calc(a,m)>calc(ln[p],m))swap(a,ln[p]);
			// 现在 a 在 m 处不优, 只可能在一侧更优
			if(r-l==1||a.k==ln[p].k)return;
			if(a.k<ln[p].k)ins(ls[p],l,m,x,y,a);
			else ins(rs[p],m,r,x,y,a);
			return;
		}
		ins(ls[p],l,m,x,y,a);
		ins(rs[p],m,r,x,y,a);
	}
	void addLine(Line a){ins(root,lo,hi,lo,hi,a);}
	void addSeg(Line a,ll x1,ll x2){ins(root,lo,hi,x1,x2,a);}
	ll query(ll x){
		ll res=LLONG_MIN;
		ll l=lo,r=hi;
		int p=root;
		while(p){
			if(has[p])res=max(res,calc(ln[p],x));
			ll m=l+(r-l)/2;
			if(x<m){
				p=ls[p];
				r=m;
			}else{
				p=rs[p];
				l=m;
			}
		}
		return res;
	}
}lc;
