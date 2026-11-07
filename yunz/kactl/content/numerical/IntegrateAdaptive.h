/**
 * Description: 自适应 Simpson 积分, 求 $\int_l^r f(x)\,dx$. 被积函数为全局函数
 * \texttt{double f(double x)}, 自己实现. 多重积分: 让 $f$ 里再调用另一个
 * 被积函数的积分 (复制一份改名即可).
 * Usage: double f(double x){return sin(x);} // 自己写 f
 * double s=integrate(0,acos(-1)); // s 约为 2
 * double t=integrate(0,1,1e-10); // 第三个参数为精度
 * Time: 与 $f$ 的光滑程度有关
 */
#pragma once

double f(double x); // 被积函数, 在别处自己实现
double simpson(double l,double r){
	double m=(l+r)/2;
	return (f(l)+4*f(m)+f(r))*(r-l)/6;
}
// dep: 至少再细分的层数, 防止一开始就误判收敛
double asr(double l,double r,double eps,double S,int dep){
	double m=(l+r)/2,L=simpson(l,m),R=simpson(m,r);
	if(dep<=0&&(fabs(L+R-S)<=15*eps||r-l<1e-10))
		return L+R+(L+R-S)/15;
	return asr(l,m,eps/2,L,dep-1)+asr(m,r,eps/2,R,dep-1);
}
double integrate(double l,double r,double eps=1e-8){
	return asr(l,r,eps,simpson(l,r),6);
}
