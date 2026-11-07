/**
 * Description: 平面点 / 向量, 几何部分其余文件都 include 它.
 * 坐标类型为 T: 默认 double; 坐标都是整数且要求精确 (凸包, 面积, 判断位置等) 时改成 typedef ll T,
 * 此时 unit, rotate, 除法以及求交点的函数会被截断, 不要用; cross, dot, len2 是坐标的二次式,
 * 坐标绝对值约 $10^9$ 以内才不溢出.
 * sgn(x) 返回 x 的符号, $|x| \le eps$ 时为 0. eps 是绝对误差 (默认 1e-9), 坐标很大时要调大.
 * == 和 < (先比 x 再比 y) 也带 eps, 可直接用于 sort, unique, set.
 * cross(a,b) 为 $a \times b$; cross(a,b,c) 为 $(b-a) \times (c-a)$: 正数表示 a, b, c 逆时针
 * (c 在 a 看向 b 的左侧), 负数为顺时针, 0 为共线.
 * angle 返回极角, 范围 $[-\pi, \pi]$. 多边形统一用 vector<Point> 存, 下标 0..n-1.
 * Usage: Point a(1,2),b(3,4),c(0,5);
 * Point s=a+b,d=b-a,m=a*2; // 向量运算
 * T k=cross(a,b),t=dot(a,b); // 叉积, 点积
 * double l=len(b-a); // 两点距离
 * if(sgn(cross(a,b,c))>0){} // a,b,c 逆时针
 * Point r=rotate(a,PI/2); // 逆时针转 90 度
 * vector<Point> poly={a,b,c}; // 多边形 poly[0..n-1]
 */
#pragma once

typedef double T; // 整数坐标可改为 ll
const double eps=1e-9;
const double PI=acos(-1.0);
int sgn(double x){ // 符号, 绝对值不超过 eps 时为 0
	if(x>eps)return 1;
	if(x<-eps)return -1;
	return 0;
}
struct Point{
	T x,y;
	Point(T x=0,T y=0):x(x),y(y){}
	Point operator+(Point b)const{return Point(x+b.x,y+b.y);}
	Point operator-(Point b)const{return Point(x-b.x,y-b.y);}
	Point operator*(T k)const{return Point(x*k,y*k);}
	Point operator/(T k)const{return Point(x/k,y/k);}
	bool operator==(Point b)const{
		return sgn(x-b.x)==0&&sgn(y-b.y)==0;
	}
	bool operator<(Point b)const{ // 先比 x 再比 y
		if(sgn(x-b.x)!=0)return x<b.x;
		return sgn(y-b.y)<0;
	}
};
T dot(Point a,Point b){return a.x*b.x+a.y*b.y;}
T cross(Point a,Point b){return a.x*b.y-a.y*b.x;}
// (b-a) 叉乘 (c-a), 大于 0 表示 a,b,c 逆时针
T cross(Point a,Point b,Point c){return cross(b-a,c-a);}
T len2(Point a){return dot(a,a);} // 长度的平方
double len(Point a){return sqrt((double)len2(a));}
double angle(Point a){return atan2(a.y,a.x);} // 极角 [-pi,pi]
Point perp(Point a){return Point(-a.y,a.x);} // 逆时针转 90 度
Point unit(Point a){return a/len(a);} // 单位向量
Point rotate(Point a,double t){ // 绕原点逆时针转 t 弧度
	return Point(a.x*cos(t)-a.y*sin(t),a.x*sin(t)+a.y*cos(t));
}
