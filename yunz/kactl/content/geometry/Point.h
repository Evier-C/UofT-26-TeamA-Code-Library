/**
 * Description: 平面点 / 向量, 其余几何文件都 include 它.
 * 坐标类型 T 默认 double; 整数坐标要求精确时改成 typedef ll T, 此时不要用 unit, rotate, 除法和求交点的函数,
 * 坐标绝对值约 $10^9$ 以内才不溢出. eps 为绝对误差 (默认 1e-9), 坐标很大时要调大; == 和 < 也带 eps.
 * Usage: Point a(1,2),b(3,4),c(0,5);
 * Point s=a+b,d=b-a,m=a*2,q=a/2; // 向量运算
 * T k=a.cross(b),t=a.dot(b); // 叉积, 点积
 * // a.cross(b,c) 即 (b-a) 叉乘 (c-a)
 * int o=sgn(a.cross(b,c)); // 1 逆时针, -1 顺时针, 0 共线
 * double l=(b-a).len(); // 两点距离, len2() 为平方
 * double th=a.angle(); // 极角, 范围 [-pi,pi]
 * Point p=a.perp(); // 逆时针转 90 度
 * Point u=a.unit(); // 单位向量
 * Point r=a.rotate(PI/2); // 绕原点逆时针转 pi/2
 * bool e=(a==b),lt=(a<b); // 带 eps, 先比 x 再比 y
 * vector<Point> poly={a,b,c}; // 多边形 poly[0..n-1]
 * sort(poly.begin(),poly.end()); // 可直接 sort, unique
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
	T dot(Point b)const{return x*b.x+y*b.y;}
	T cross(Point b)const{return x*b.y-y*b.x;}
	// (b-a) 叉乘 (c-a), a 为自身, 大于 0 表示逆时针
	T cross(Point b,Point c)const{
		return (b-*this).cross(c-*this);
	}
	T len2()const{return x*x+y*y;} // 长度的平方
	double len()const{return sqrt((double)len2());}
	double angle()const{return atan2(y,x);} // 极角 [-pi,pi]
	Point perp()const{return Point(-y,x);} // 逆时针转 90 度
	Point unit()const{return *this/len();} // 单位向量
	Point rotate(double t)const{ // 绕原点逆时针转 t 弧度
		return Point(x*cos(t)-y*sin(t),x*sin(t)+y*cos(t));
	}
};
