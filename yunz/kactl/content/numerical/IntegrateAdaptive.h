/**
 * Description: 自适应 Simpson 积分: 求 $\int_l^r f(x)\,dx$.
 * 被积函数是全局函数 \texttt{double f(double x)}, 自己实现 (模板里只有声明).
 * \texttt{integrate(l, r, eps)} 返回积分值, eps 为允许误差 (默认 $10^{-8}$).
 * 每段先用 Simpson 公式估计, 左右两半之和与整段相差不超过 $15 \cdot eps$ 就停止,
 * 否则递归两半 (eps 减半). 开头强制细分 6 层, 防止在对称函数上一开始误判收敛.
 * 适用于光滑函数; 有尖点或间断时在这些点处把区间拆开分别积分更准.
 * 二重积分: 写 g(x) 对 y 积分, 需要再复制一份本模板并改名.
 * Usage: double f(double x){return sin(x);} // 自己写
 * double s=integrate(0,acos(-1)); // s 约为 2
 * double t=integrate(0,1,1e-10); // 指定精度
 * Time: 与 $f$ 的光滑程度有关, 一般几千次 $f$ 调用
 */
#pragma once

double f(double x); // 被积函数, 在别处自己实现
double simpson(double l,double r){
	double m=(l+r)/2;
	return (f(l)+4*f(m)+f(r))*(r-l)/6;
}
// S 为整段的 Simpson 值, dep 为至少还要细分的层数
double asr(double l,double r,double eps,double S,int dep){
	double m=(l+r)/2;
	double L=simpson(l,m);
	double R=simpson(m,r);
	if(dep<=0&&(fabs(L+R-S)<=15*eps||r-l<1e-10)){
		return L+R+(L+R-S)/15;
	}
	return asr(l,m,eps/2,L,dep-1)+asr(m,r,eps/2,R,dep-1);
}
double integrate(double l,double r,double eps=1e-8){
	return asr(l,r,eps,simpson(l,r),6);
}
