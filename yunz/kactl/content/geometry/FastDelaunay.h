/**
 * Author: Philippe Legault
 * Date: 2016
 * License: MIT
 * Source: https://github.com/Bathlamos/delaunay-triangulation/
 * Description: 快速 Delaunay 三角剖分.
 * 每个三角形的外接圆内都不含任何输入点.
 * 不能有重复点. 若所有点共线, 不返回任何三角形.
 * 也可用于 double, 但 circ 中可能有精度问题.
 * 三角形按 \{t[0][0], t[0][1], t[0][2], t[1][0], \dots\} 的顺序返回, 均为逆时针.
 * Usage:
 * 	vector<P> t = triangulate(pts);
 * 	// 第 i 个三角形为 t[3*i], t[3*i+1], t[3*i+2]
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

typedef Point<ll>P;
typedef struct Quad*Q;
typedef __int128_t lll; // 坐标小于 2e4 时可用 ll
P arb(LLONG_MAX,LLONG_MAX); // 不等于任何其他点

struct Quad{
	Q rot,o;P p=arb;bool mark;
	P&F(){return r()->p;}
	Q&r(){return rot->rot;}
	Q prev(){return rot->o->rot;}
	Q next(){return r()->prev();}
}*H;

bool circ(P p,P a,P b,P c){ // p 是否在外接圆内
	lll p2=p.dist2(),A=a.dist2()-p2,
	    B=b.dist2()-p2,C=c.dist2()-p2;
	return p.cross(a,b)*C+p.cross(b,c)*A+p.cross(c,a)*B>0;
}
Q makeEdge(P orig,P dest){
	Q r=H?H:new Quad{new Quad{new Quad{new Quad{0}}}};
	H=r->o;r->r()->r()=r;
	rep(i,0,4)r=r->rot,r->p=arb,r->o=i&1?r:r->r();
	r->p=orig;r->F()=dest;
	return r;
}
void splice(Q a,Q b){
	swap(a->o->rot->o,b->o->rot->o);swap(a->o,b->o);
}
Q connect(Q a,Q b){
	Q q=makeEdge(a->F(),b->p);
	splice(q,a->next());
	splice(q->r(),b);
	return q;
}

pair<Q,Q>rec(const vector<P>&s){
	if(sz(s)<=3){
		Q a=makeEdge(s[0],s[1]),b=makeEdge(s[1],s.back());
		if(sz(s)==2)return {a,a->r()};
		splice(a->r(),b);
		auto side=s[0].cross(s[1],s[2]);
		Q c=side?connect(b,a):0;
		return {side<0?c->r():a,side<0?c:b->r()};
	}

#define H(e) e->F(), e->p
#define valid(e) (e->F().cross(H(base)) > 0)
	Q A,B,ra,rb;
	int half=sz(s)/2;
	tie(ra,A)=rec({all(s)-half});
	tie(B,rb)=rec({sz(s)-half+all(s)});
	while((B->p.cross(H(A))<0&&(A=A->next()))||
	       (A->p.cross(H(B))>0&&(B=B->r()->o)));
	Q base=connect(B->r(),A);
	if(A->p==ra->p)ra=base->r();
	if(B->p==rb->p)rb=base;

#define DEL(e, init, dir) Q e = init->dir; if (valid(e)) \
		while (circ(e->dir->F(), H(base), e->F())) { \
			Q t = e->dir; \
			splice(e, e->prev()); \
			splice(e->r(), e->r()->prev()); \
			e->o = H; H = e; e = t; \
		}
	for(;;){
		DEL(LC,base->r(),o);DEL(RC,base,prev());
		if(!valid(LC)&&!valid(RC))break;
		if(!valid(LC)||(valid(RC)&&circ(H(RC),H(LC))))
			base=connect(RC,base->r());
		else
			base=connect(base->r(),LC->r());
	}
	return {ra,rb};
}

vector<P>triangulate(vector<P>pts){
	sort(all(pts));assert(unique(all(pts))==pts.end());
	if(sz(pts)<2)return {};
	Q e=rec(pts).first;
	vector<Q>q={e};
	int qi=0;
	while(e->o->F().cross(e->F(),e->p)<0)e=e->o;
#define ADD { Q c = e; do { c->mark = 1; pts.push_back(c->p); \
	q.push_back(c->r());c=c->next();}while(c!=e);}
	ADD;pts.clear();
	while(qi<sz(q))if(!(e=q[qi++])->mark)ADD;
	return pts;
}
