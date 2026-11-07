/**
 * Description: 李超树, 整数 x 取值于 [lo, hi), 动态开点, 不用离散化.
 * addLine 插入直线 $y = kx + b$, addSeg 插入只在 $x \in [x_1, x_2)$ 上存在的线段.
 * query(x) 返回 x 处的最大值, 没有线段覆盖 x 时返回 LLONG\_MIN.
 * 求最小值: 插入 $(-k, -b)$, 再把答案取负.
 * 要求 $|kx + b| < 9 \cdot 10^{18}$, $hi - lo < 9 \cdot 10^{18}$.
 * Usage: init(-1e9, 1e9 + 1); // 每组数据调用一次
 * addLine({k, b}); addSeg({k, b}, x1, x2); ll y = query(x);
 * Time: 直线和查询 $O(\log C)$, 线段 $O(\log^2 C)$, $C = hi - lo$
 */
#pragma once

// 节点数: 每条直线最多 1 个, 每条线段最多约 2 log C 个
const int M=4e6+5;
struct Line{ll k,b;};
Line ln[M];
int ls[M],rs[M],tot,root;bool has[M]; // has: 节点上有线
ll lo,hi;
ll calc(Line a,ll x){return a.k*x+a.b;}
void init(ll L,ll R){lo=L,hi=R,tot=root=0;}
// 节点 p 管 [l, r), 在 [x, y) 上插入 a
void ins(int&p,ll l,ll r,ll x,ll y,Line a){
	if(y<=l||r<=x)return;
	if(!p)p=++tot,ls[p]=rs[p]=0,has[p]=0;
	ll m=l+(r-l)/2;
	if(x<=l&&r<=y){
		if(!has[p]){ln[p]=a,has[p]=1;return;}
		if(calc(a,m)>calc(ln[p],m))swap(a,ln[p]);
		// 现在 a 在 m 处不优, 只可能在一侧更优
		if(r-l==1||a.k==ln[p].k)return;
		if(a.k<ln[p].k)ins(ls[p],l,m,x,y,a);
		else ins(rs[p],m,r,x,y,a);
		return;
	}
	ins(ls[p],l,m,x,y,a),ins(rs[p],m,r,x,y,a);
}
void addLine(Line a){ins(root,lo,hi,lo,hi,a);}
void addSeg(Line a,ll x1,ll x2){ins(root,lo,hi,x1,x2,a);}
ll query(ll x){
	ll res=LLONG_MIN,l=lo,r=hi;
	for(int p=root;p;){
		if(has[p])res=max(res,calc(ln[p],x));
		ll m=l+(r-l)/2;
		if(x<m)p=ls[p],r=m;
		else p=rs[p],l=m;
	}
	return res;
}
