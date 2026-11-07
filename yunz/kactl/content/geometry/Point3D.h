/**
 * Author: Ulf Lundstrom with inspiration from tinyKACTL
 * Date: 2009-04-14
 * License: CC0
 * Source:
 * Description: 三维空间点类. T 可取 double 或 long long.
 * Usage:
 * 	typedef Point3D<double> P3; P3 a(1, 0, 0), b(0, 1, 0);
 * 	P3 n = a.cross(b); double d = a.dot(b), l = n.dist();
 * Status: tested, except for phi and theta
 */
#pragma once

template<class T>struct Point3D{
	typedef Point3D P;
	typedef const P&R;
	T x,y,z;
	explicit Point3D(T x=0,T y=0,T z=0):x(x),y(y),z(z){}
	bool operator<(R p)const{
		return tie(x,y,z)<tie(p.x,p.y,p.z);}
	bool operator==(R p)const{
		return tie(x,y,z)==tie(p.x,p.y,p.z);}
	P operator+(R p)const{return P(x+p.x,y+p.y,z+p.z);}
	P operator-(R p)const{return P(x-p.x,y-p.y,z-p.z);}
	P operator*(T d)const{return P(x*d,y*d,z*d);}
	P operator/(T d)const{return P(x/d,y/d,z/d);}
	T dot(R p)const{return x*p.x+y*p.y+z*p.z;}
	P cross(R p)const{
		return P(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);
	}
	T dist2()const{return x*x+y*y+z*z;}
	double dist()const{return sqrt((double)dist2());}
	// 方位角 即经度 与 x 轴夹角 取值 [-pi, pi]
	double phi()const{return atan2(y,x);}
	// 天顶角 即纬度 与 z 轴夹角 取值 [0, pi]
	double theta()const{return atan2(sqrt(x*x+y*y),z);}
	P unit()const{return *this/(T)dist();} // 长度变为 1
	// 与 *this 和 p 都垂直的单位向量
	P normal(P p)const{return cross(p).unit();}
	// 绕 axis 逆时针旋转 angle 弧度
	P rotate(double angle,P axis)const{
		double s=sin(angle),c=cos(angle);P u=axis.unit();
		return u*dot(u)*(1-c)+(*this)*c-cross(u)*s;
	}
};
