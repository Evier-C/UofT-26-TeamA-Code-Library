/**
 * Description: 李超树: 插入直线或线段, 查询整数 x 处的最大值. x 取值于 [lo, hi).
 * 要求 $|kx + b| < 9 \cdot 10^{18}$. 节点数 M: 每条直线 1 个, 每条线段约
 * 2 log C 个; 默认 4e6, 约 100MB, 对象必须是全局变量.
 * Usage: lc.init(-1e9, 1e9 + 1); // x 的范围, 每组数据调用
 * lc.addLine({2, 3}); // y = 2x + 3
 * lc.addSeg({-1, 10}, 0, 5); // y = -x + 10, 只在 x = 0..4 上
 * ll y = lc.query(x); // 最大值, 没有线覆盖 x 时为 LLONG_MIN
 * // 求最小值: 插入 (-k, -b), 答案取负
 * lc.addLine({-k, -b}); ll mn = -lc.query(x);
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
