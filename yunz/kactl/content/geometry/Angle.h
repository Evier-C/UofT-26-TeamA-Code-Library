/**
 * Author: Simon Lindholm
 * Date: 2015-01-31
 * License: CC0
 * Source: me
 * Description: 用于给角度排序的类 (角度用 int 点加上绕原点的圈数表示).
 *  适用于极角扫描. 有时也用来表示点或向量.
 * Usage:
 *  vector<Angle> v = {w[0], w[0].t360() ...}; sort(all(v));
 *  int j = 0; rep(i,0,n) { while (v[j] < v[i].t180()) ++j; }
 *  // 扫描 j, 使 j-i 等于以 0 和 i 为顶点的正向三角形个数
 * Status: Used, works well
 */
#pragma once

struct Angle{
	int x,y;
	int t;
	Angle(int x,int y,int t=0):x(x),y(y),t(t){}
	Angle operator-(Angle b)const{return {x-b.x,y-b.y,t};}
	int half()const{ // 角在 [pi, 2pi) 内时为真
		assert(x||y); // 可按需改哪一半算较大
		return y<0||(y==0&&x<0);
	}
	Angle t90()const{return {-y,x,t+(half()&&x>=0)};}
	Angle t180()const{return {-x,-y,t+half()};}
	Angle t360()const{return {x,y,t+1};}
};
bool operator<(Angle a,Angle b){ // 比较 [0, 2pi) 内的角
	// 加入 a.dist2() 和 b.dist2() 可同时比较距离
	return make_tuple(a.t,a.half(),a.y*(ll)b.x)<
	       make_tuple(b.t,b.half(),a.x*(ll)b.y);
}

// 给定两点 求它们之间的最小角
// 即覆盖这条线段的角
pair<Angle,Angle>segmentAngles(Angle a,Angle b){
	if(b<a)swap(a,b);
	return (b<a.t180()?
	        make_pair(a,b):make_pair(b,a.t360()));
}
Angle operator+(Angle a,Angle b){ // 点 a 加向量 b
	Angle r(a.x+b.x,a.y+b.y,a.t);
	if(a.t180()<r)r.t--;
	return r.t180()<a?r.t360():r;
}
Angle angleDiff(Angle a,Angle b){ // 角 b 减去角 a
	int tu=b.t-a.t;a.t=b.t;
	return {a.x*b.x+a.y*b.y,a.x*b.y-a.y*b.x,tu-(b<a)};
}
