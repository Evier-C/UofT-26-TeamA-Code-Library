/**
 * Description: 平面点 / 向量, 几何部分的公共头文件 (其余文件都用它).
 * 坐标类型由 T 决定, 默认 double; 整数坐标要求精确时改成 typedef ll T,
 * 此时不要用 unit, rotate 和除法. sgn 按 eps 判符号, == 和 < 也带 eps.
 * 多边形用 vector<Point> 存, 下标从 0 开始.
 * Usage: Point a(1,2),b(3,4);
 * T c=cross(a,b),d=dot(a,b); // 叉积, 点积
 * double l=len(b-a); // 两点距离
 * if(sgn(cross(a,b,c))>0) // a,b,c 逆时针
 * vector<Point> poly; // 顶点 poly[0..n-1]
 */
#pragma once

typedef double T; // 整数坐标可改为 ll
const double eps=1e-9,PI=acos(-1.0);
int sgn(double x){return x<-eps?-1:x>eps;}
struct Point{
	T x,y;
	Point(T x=0,T y=0):x(x),y(y){}
	Point operator+(Point b)const{return Point(x+b.x,y+b.y);}
	Point operator-(Point b)const{return Point(x-b.x,y-b.y);}
	Point operator*(T k)const{return Point(x*k,y*k);}
	Point operator/(T k)const{return Point(x/k,y/k);}
	bool operator==(Point b)const{
		return !sgn(x-b.x)&&!sgn(y-b.y);}
	bool operator<(Point b)const{ // 先比 x 再比 y
		return sgn(x-b.x)?x<b.x:sgn(y-b.y)<0;}
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
	return Point(a.x*cos(t)-a.y*sin(t),a.x*sin(t)+a.y*cos(t));}
