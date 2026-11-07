/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: KD 树 (二维, 可扩展到三维), 求最近点.
 * Usage:
 * 	KDTree kd(pts); pair<T, P> r = kd.nearest(p);
 * 	// 最近点为 r.second, 平方距离为 r.first
 * Status: Tested on excellentengineers
 */
#pragma once

#include "Point.h"

typedef long long T;
typedef Point<T>P;
const T INF=numeric_limits<T>::max();

bool on_x(const P&a,const P&b){return a.x<b.x;}
bool on_y(const P&a,const P&b){return a.y<b.y;}

struct Node{
	P pt; // 若为叶子则存其唯一的点
	T x0=INF,x1=-INF,y0=INF,y1=-INF; // 包围盒
	Node*first=0,*second=0;

	T distance(const P&p){ // 到点 p 的最小平方距离
		T x=(p.x<x0?x0:p.x>x1?x1:p.x);
		T y=(p.y<y0?y0:p.y>y1?y1:p.y);
		return (P(x,y)-p).dist2();
	}

	Node(vector<P>&&vp):pt(vp[0]){
		for(P p:vp){
			x0=min(x0,p.x);x1=max(x1,p.x);
			y0=min(y0,p.y);y1=max(y1,p.y);
		}
		if(vp.size()>1){
			// 宽不小于高时按 x 划分
			sort(all(vp),x1-x0>=y1-y0?on_x:on_y);
			// 两个儿子各取一半 中间重复点多时较慢
			int half=sz(vp)/2;
			first=new Node({vp.begin(),vp.begin()+half});
			second=new Node({vp.begin()+half,vp.end()});
		}
	}
};

struct KDTree{
	Node*root;
	KDTree(const vector<P>&vp):root(new Node({all(vp)})){}

	pair<T,P>search(Node*node,const P&p){
		if(!node->first){
			// 若不应找到 p 自身 则取消下一行注释
			// if (p == node->pt) return {INF, P()};
			return make_pair((p-node->pt).dist2(),node->pt);
		}

		Node*f=node->first,*s=node->second;
		T bfirst=f->distance(p),bsec=s->distance(p);
		if(bfirst>bsec)swap(bsec,bfirst),swap(f,s);

		// 先搜近的一侧 必要时再搜另一侧
		auto best=search(f,p);
		if(bsec<best.first)
			best=min(best,search(s,p));
		return best;
	}

	// 求离 p 最近的点及其平方距离
	// 需要 Point 定义某种 operator<
	pair<T,P>nearest(const P&p){
		return search(root,p);
	}
};
