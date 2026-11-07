/**
 * Author: Simon Lindholm
 * Date: 2016-07-25
 * Source: https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/DataStructure/LinkCutTree.h
 * Description: 维护无根树构成的森林. 可以加边和删边 (要求结果仍是森林),
 * 并查询两点是否在同一棵树中.
 * Usage: LinkCut lc(N); lc.link(u, v); lc.cut(u, v);
 * bool b = lc.connected(u, v);
 * Time: 所有操作均摊 O(\log N).
 * Status: Stress-tested a bit for N <= 20
 */
#pragma once

struct Node{ // Splay 树 . 根的 pp 存原树中的父亲
	Node*p=0,*pp=0,*c[2];
	bool flip=0;
	Node(){c[0]=c[1]=0;fix();}
	void fix(){
		if(c[0])c[0]->p=this;
		if(c[1])c[1]->p=this;
		// 需要时在此更新子树和等信息
	}
	void pushFlip(){
		if(!flip)return;
		flip=0;swap(c[0],c[1]);
		if(c[0])c[0]->flip^=1;
		if(c[1])c[1]->flip^=1;
	}
	int up(){return p?p->c[1]==this:-1;}
	void rot(int i,int b){
		int h=i^b;
		Node*x=c[i],*y=b==2?x:x->c[h],*z=b?y:x;
		if((y->p=p))p->c[up()]=y;
		c[i]=z->c[i^1];
		if(b<2){
			x->c[h]=y->c[h^1];
			y->c[h^1]=x;
		}
		z->c[i^1]=this;
		fix();x->fix();y->fix();
		if(p)p->fix();
		swap(pp,y->pp);
	}
	void splay(){ /// 把自己 splay 到根 , 结束时 flip 为 0
		for(pushFlip();p;){
			if(p->p)p->p->pushFlip();
			p->pushFlip();pushFlip();
			int c1=up(),c2=p->up();
			if(c2==-1)p->rot(c1,2);
			else p->p->rot(c2,c1!=c2);
		}
	}
	Node*first(){ /// 返回子树最小元素 , 并把它 splay 到顶
		pushFlip();
		return c[0]?c[0]->first():(splay(),this);
	}
};

struct LinkCut{
	vector<Node>node;
	LinkCut(int N):node(N){}

	void link(int u,int v){ // 加边 (u, v)
		assert(!connected(u,v));
		makeRoot(&node[u]);
		node[u].pp=&node[v];
	}
	void cut(int u,int v){ // 删边 (u, v)
		Node*x=&node[u],*top=&node[v];
		makeRoot(top);x->splay();
		assert(top==(x->pp?:x->c[0]));
		if(x->pp)x->pp=0;
		else{
			x->c[0]=top->p=0;
			x->fix();
		}
	}
	bool connected(int u,int v){ // u , v 是否在同一棵树
		Node*nu=access(&node[u])->first();
		return nu==access(&node[v])->first();
	}
	void makeRoot(Node*u){ /// 把 u 变为所在原树的根
		access(u);
		u->splay();
		if(u->c[0]){
			u->c[0]->p=0;
			u->c[0]->flip^=1;
			u->c[0]->pp=u;
			u->c[0]=0;
			u->fix();
		}
	}
	Node*access(Node*u){ /// 把 u 移到根辅助树 , 返回其根
		u->splay();
		while(Node*pp=u->pp){
			pp->splay();u->pp=0;
			if(pp->c[1]){
				pp->c[1]->p=0;pp->c[1]->pp=pp;}
			pp->c[1]=u;pp->fix();u=pp;
		}
		return u;
	}
};
