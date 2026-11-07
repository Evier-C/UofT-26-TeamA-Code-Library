// Checks the default LazySegmentTree and every code block in the lazy-tag guide
// (data-structures/chapter.tex) against brute force. Seg is copied from LazySegmentTree.h.
#include "../utilities/template.h"
namespace assign {
struct T { ll sum, mx; int len; };
struct U{ll v;bool has;};
const U idU={0,0};
const T idT = {0, LLONG_MIN, 0};
T f(T a, T b) {
	return {a.sum + b.sum, max(a.mx, b.mx), a.len + b.len};
}
struct Seg{
	int n;vector<T>t;vector<U>d;
	Seg(const vector<T>&a):n(sz(a)),t(4*n),d(4*n,idU){
		build(1,0,n,a);
	}
	void build(int x,int l,int r,const vector<T>&a){
		if(r-l==1){t[x]=a[l];return;}
		int m=(l+r)/2;
		build(2*x,l,m,a),build(2*x+1,m,r,a);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	void app(int x,U u){ // 整段赋成 u.v
		t[x].sum=u.v*t[x].len,t[x].mx=u.v;
		d[x]=u; // 新赋值直接覆盖旧标记
	}
	void push(int x){
		if(!d[x].has)return;
		app(2*x,d[x]),app(2*x+1,d[x]),d[x]=idU;
	}
	void update(int L,int R,U u){upd(L,R,u,1,0,n);}
	void upd(int L,int R,U u,int x,int l,int r){
		if(R<=l||r<=L)return;
		if(L<=l&&r<=R)return app(x,u);
		push(x);
		int m=(l+r)/2;
		upd(L,R,u,2*x,l,m);
		upd(L,R,u,2*x+1,m,r);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	T query(int L,int R){return qry(L,R,1,0,n);}
	T qry(int L,int R,int x,int l,int r){
		if(R<=l||r<=L)return idT;
		if(L<=l&&r<=R)return t[x];
		push(x);
		int m=(l+r)/2;
		return f(qry(L,R,2*x,l,m),
		         qry(L,R,2*x+1,m,r));
	}
};
}

namespace assignadd {
struct T { ll sum, mx; int len; };
// 标记含义: 若 has 先赋成 s, 再加 add
struct U{ll s;bool has;ll add;};
const U idU={0,0,0};
const T idT = {0, LLONG_MIN, 0};
T f(T a, T b) {
	return {a.sum + b.sum, max(a.mx, b.mx), a.len + b.len};
}
struct Seg{
	int n;vector<T>t;vector<U>d;
	Seg(const vector<T>&a):n(sz(a)),t(4*n),d(4*n,idU){
		build(1,0,n,a);
	}
	void build(int x,int l,int r,const vector<T>&a){
		if(r-l==1){t[x]=a[l];return;}
		int m=(l+r)/2;
		build(2*x,l,m,a),build(2*x+1,m,r,a);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	void app(int x,U u){
		T&a=t[x];U&e=d[x];
		if(u.has)
			a.sum=u.s*a.len,a.mx=u.s,e={u.s,1,0};
		a.sum+=u.add*a.len,a.mx+=u.add,e.add+=u.add;
	}
	void push(int x){
		if(!d[x].has&&!d[x].add)return;
		app(2*x,d[x]),app(2*x+1,d[x]),d[x]=idU;
	}
	void update(int L,int R,U u){upd(L,R,u,1,0,n);}
	void upd(int L,int R,U u,int x,int l,int r){
		if(R<=l||r<=L)return;
		if(L<=l&&r<=R)return app(x,u);
		push(x);
		int m=(l+r)/2;
		upd(L,R,u,2*x,l,m);
		upd(L,R,u,2*x+1,m,r);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	T query(int L,int R){return qry(L,R,1,0,n);}
	T qry(int L,int R,int x,int l,int r){
		if(R<=l||r<=L)return idT;
		if(L<=l&&r<=R)return t[x];
		push(x);
		int m=(l+r)/2;
		return f(qry(L,R,2*x,l,m),
		         qry(L,R,2*x+1,m,r));
	}
};
}

namespace affine {

const ll M=998244353;
struct T{ll sum;int len;};struct U{ll a,b;};
const T idT={0,0};const U idU={1,0};
T f(T x,T y){
	return {(x.sum+y.sum)%M,x.len+y.len};
}

struct Seg{
	int n;vector<T>t;vector<U>d;
	Seg(const vector<T>&a):n(sz(a)),t(4*n),d(4*n,idU){
		build(1,0,n,a);
	}
	void build(int x,int l,int r,const vector<T>&a){
		if(r-l==1){t[x]=a[l];return;}
		int m=(l+r)/2;
		build(2*x,l,m,a),build(2*x+1,m,r,a);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	void app(int x,U u){ // 整段每个数 v 变成 a * v + b
		t[x].sum=(u.a*t[x].sum+u.b*t[x].len)%M;
		d[x]={u.a*d[x].a%M,(u.a*d[x].b+u.b)%M};
	}
	void push(int x){
		if(d[x].a==1&&!d[x].b)return;
		app(2*x,d[x]),app(2*x+1,d[x]),d[x]=idU;
	}
	void update(int L,int R,U u){upd(L,R,u,1,0,n);}
	void upd(int L,int R,U u,int x,int l,int r){
		if(R<=l||r<=L)return;
		if(L<=l&&r<=R)return app(x,u);
		push(x);
		int m=(l+r)/2;
		upd(L,R,u,2*x,l,m);
		upd(L,R,u,2*x+1,m,r);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	T query(int L,int R){return qry(L,R,1,0,n);}
	T qry(int L,int R,int x,int l,int r){
		if(R<=l||r<=L)return idT;
		if(L<=l&&r<=R)return t[x];
		push(x);
		int m=(l+r)/2;
		return f(qry(L,R,2*x,l,m),
		         qry(L,R,2*x+1,m,r));
	}
};
}

namespace flip {

struct T{int cnt,len;};struct U{bool r;};
const T idT={0,0};const U idU={0};
T f(T a,T b){return {a.cnt+b.cnt,a.len+b.len};}

struct Seg{
	int n;vector<T>t;vector<U>d;
	Seg(const vector<T>&a):n(sz(a)),t(4*n),d(4*n,idU){
		build(1,0,n,a);
	}
	void build(int x,int l,int r,const vector<T>&a){
		if(r-l==1){t[x]=a[l];return;}
		int m=(l+r)/2;
		build(2*x,l,m,a),build(2*x+1,m,r,a);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	void app(int x,U u){ // 整段 0 和 1 互换
		if(u.r)t[x].cnt=t[x].len-t[x].cnt,d[x].r^=1;
	}
	void push(int x){
		if(!d[x].r)return;
		app(2*x,d[x]),app(2*x+1,d[x]),d[x]=idU;
	}
	void update(int L,int R,U u){upd(L,R,u,1,0,n);}
	void upd(int L,int R,U u,int x,int l,int r){
		if(R<=l||r<=L)return;
		if(L<=l&&r<=R)return app(x,u);
		push(x);
		int m=(l+r)/2;
		upd(L,R,u,2*x,l,m);
		upd(L,R,u,2*x+1,m,r);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	T query(int L,int R){return qry(L,R,1,0,n);}
	T qry(int L,int R,int x,int l,int r){
		if(R<=l||r<=L)return idT;
		if(L<=l&&r<=R)return t[x];
		push(x);
		int m=(l+r)/2;
		return f(qry(L,R,2*x,l,m),
		         qry(L,R,2*x+1,m,r));
	}
};
}

namespace maxsub {

const ll NEG=-(ll)1e18;
struct T{ll sum,pre,suf,best;};
struct U{ll v;};
const T idT={0,NEG,NEG,NEG};
const U idU={0};
T f(T a,T b){
	return {a.sum+b.sum,max(a.pre,a.sum+b.pre),
	        max(b.suf,b.sum+a.suf),
	        max({a.best,b.best,a.suf+b.pre})};
}

struct Seg{
	int n;vector<T>t;vector<U>d;
	Seg(const vector<T>&a):n(sz(a)),t(4*n),d(4*n,idU){
		build(1,0,n,a);
	}
	void build(int x,int l,int r,const vector<T>&a){
		if(r-l==1){t[x]=a[l];return;}
		int m=(l+r)/2;
		build(2*x,l,m,a),build(2*x+1,m,r,a);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	void app(int x,U u){ // 只会落在叶子上
		t[x]={u.v,u.v,u.v,u.v};
	}
	void push(int){}
	void update(int L,int R,U u){upd(L,R,u,1,0,n);}
	void upd(int L,int R,U u,int x,int l,int r){
		if(R<=l||r<=L)return;
		if(L<=l&&r<=R)return app(x,u);
		push(x);
		int m=(l+r)/2;
		upd(L,R,u,2*x,l,m);
		upd(L,R,u,2*x+1,m,r);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	T query(int L,int R){return qry(L,R,1,0,n);}
	T qry(int L,int R,int x,int l,int r){
		if(R<=l||r<=L)return idT;
		if(L<=l&&r<=R)return t[x];
		push(x);
		int m=(l+r)/2;
		return f(qry(L,R,2*x,l,m),
		         qry(L,R,2*x+1,m,r));
	}
};
}

namespace def {


struct T{ll sum,mx;int len;}; // 节点信息
struct U{ll add;}; // 懒标记
const T idT={0,LLONG_MIN,0};
const U idU={0};
T f(T a,T b){
	return {a.sum+b.sum,max(a.mx,b.mx),a.len+b.len};
}

struct Seg{
	int n;vector<T>t;vector<U>d;
	Seg(const vector<T>&a):n(sz(a)),t(4*n),d(4*n,idU){
		build(1,0,n,a);
	}
	void build(int x,int l,int r,const vector<T>&a){
		if(r-l==1){t[x]=a[l];return;}
		int m=(l+r)/2;
		build(2*x,l,m,a),build(2*x+1,m,r,a);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	void app(int x,U u){ // 整段 x 打上标记 u
		t[x].sum+=u.add*t[x].len,t[x].mx+=u.add;
		d[x].add+=u.add;
	}
	void push(int x){ // 有标记才下传给两个儿子
		if(!d[x].add)return;
		app(2*x,d[x]),app(2*x+1,d[x]),d[x]=idU;
	}
	void update(int L,int R,U u){upd(L,R,u,1,0,n);}
	void upd(int L,int R,U u,int x,int l,int r){
		if(R<=l||r<=L)return;
		if(L<=l&&r<=R)return app(x,u);
		push(x);
		int m=(l+r)/2;
		upd(L,R,u,2*x,l,m);
		upd(L,R,u,2*x+1,m,r);
		t[x]=f(t[2*x],t[2*x+1]);
	}
	T query(int L,int R){return qry(L,R,1,0,n);}
	T qry(int L,int R,int x,int l,int r){
		if(R<=l||r<=L)return idT;
		if(L<=l&&r<=R)return t[x];
		push(x);
		int m=(l+r)/2;
		return f(qry(L,R,2*x,l,m),
		         qry(L,R,2*x+1,m,r));
	}
};
}


mt19937 rng(11);
int rnd(int lo, int hi) { return lo + (int)(rng() % (unsigned)(hi - lo + 1)); }
long long checks = 0;
void lr(int n, int& l, int& r) { l = rnd(0, n - 1); r = rnd(l + 1, n); }
template<class S, class TT> void chk(S& s, int l, int r, vector<ll>& a, TT) {}
int main() {
	rep(it, 0, 1500) { int n = rnd(1, 40); vector<ll> a(n); vector<def::T> in(n);
		rep(i, 0, n) a[i] = rnd(-50, 50), in[i] = {a[i], a[i], 1}; def::Seg s(in);
		rep(st, 0, 100) { int l, r; lr(n, l, r);
			if (rng() % 2) { ll v = rnd(-50, 50); s.update(l, r, {v}); rep(i, l, r) a[i] += v; }
			else { auto q = s.query(l, r); ll sm = 0, mx = LLONG_MIN; rep(i, l, r) sm += a[i], mx = max(mx, a[i]);
				assert(q.sum == sm && q.mx == mx && q.len == r - l); checks++; } } }
	rep(it, 0, 1500) { int n = rnd(1, 40); vector<ll> a(n); vector<assign::T> in(n);
		rep(i, 0, n) a[i] = rnd(-50, 50), in[i] = {a[i], a[i], 1}; assign::Seg s(in);
		rep(st, 0, 100) { int l, r; lr(n, l, r);
			if (rng() % 2) { ll v = rnd(-50, 50); s.update(l, r, {v, 1}); rep(i, l, r) a[i] = v; }
			else { auto q = s.query(l, r); ll sm = 0, mx = LLONG_MIN; rep(i, l, r) sm += a[i], mx = max(mx, a[i]);
				assert(q.sum == sm && q.mx == mx); checks++; } } }
	rep(it, 0, 1500) { int n = rnd(1, 40); vector<ll> a(n); vector<assignadd::T> in(n);
		rep(i, 0, n) a[i] = rnd(-50, 50), in[i] = {a[i], a[i], 1}; assignadd::Seg s(in);
		rep(st, 0, 100) { int l, r; lr(n, l, r); int op = rnd(0, 2);
			if (op == 0) { ll v = rnd(-50, 50); s.update(l, r, {v, 1, 0}); rep(i, l, r) a[i] = v; }
			else if (op == 1) { ll v = rnd(-50, 50); s.update(l, r, {0, 0, v}); rep(i, l, r) a[i] += v; }
			else { auto q = s.query(l, r); ll sm = 0, mx = LLONG_MIN; rep(i, l, r) sm += a[i], mx = max(mx, a[i]);
				assert(q.sum == sm && q.mx == mx); checks++; } } }
	rep(it, 0, 1500) { int n = rnd(1, 40); vector<ll> a(n); vector<affine::T> in(n);
		rep(i, 0, n) a[i] = rnd(0, 1000000), in[i] = {a[i], 1}; affine::Seg s(in);
		rep(st, 0, 100) { int l, r; lr(n, l, r);
			if (rng() % 2) { ll x = rnd(0, 998244352), y = rnd(0, 998244352); s.update(l, r, {x, y});
				rep(i, l, r) a[i] = (x * a[i] + y) % affine::M; }
			else { ll sm = 0; rep(i, l, r) sm = (sm + a[i]) % affine::M; assert(s.query(l, r).sum == sm); checks++; } } }
	rep(it, 0, 1500) { int n = rnd(1, 40); vector<int> a(n); vector<flip::T> in(n);
		rep(i, 0, n) a[i] = rnd(0, 1), in[i] = {a[i], 1}; flip::Seg s(in);
		rep(st, 0, 100) { int l, r; lr(n, l, r);
			if (rng() % 2) { s.update(l, r, {1}); rep(i, l, r) a[i] ^= 1; }
			else { int c = 0; rep(i, l, r) c += a[i]; assert(s.query(l, r).cnt == c); checks++; } } }
	rep(it, 0, 1500) { int n = rnd(1, 40); vector<ll> a(n); vector<maxsub::T> in(n);
		rep(i, 0, n) a[i] = rnd(-50, 50), in[i] = {a[i], a[i], a[i], a[i]}; maxsub::Seg s(in);
		rep(st, 0, 100) {
			if (rng() % 2) { int p = rnd(0, n - 1); ll v = rnd(-50, 50); s.update(p, p + 1, {v}); a[p] = v; }
			else { int l, r; lr(n, l, r); ll best = LLONG_MIN;
				rep(i, l, r) { ll c = 0; rep(j, i, r) c += a[j], best = max(best, c); }
				assert(s.query(l, r).best == best); checks++; } } }
	cout << "Template + all 5 guide blocks passed (" << checks << " checks)" << endl;
}
