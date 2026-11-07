/**
 * Description: FFT 多项式乘法, 结果四舍五入成整数. 精度: $(\sum a_i^2 + \sum b_i^2) \log_2 n
 * < 9 \cdot 10^{14}$ 时安全 (结果约 $10^{14}$ 以内); 超出用 NTT 或 FFTMod.
 * Usage: vector<ll> a={1,2},b={1,3}; // a[i] 为 x^i 的系数, 可为负
 * vector<ll> c=conv(a,b); // c={1,5,6}, 长度 |a|+|b|-1
 * // c[k]=sum a[i]*b[k-i]; 任一为空返回空
 * // 手动: f 长度为 2 的幂, fft(f,1) 正变换
 * // fft(f,-1) 逆变换, 已除以 n
 * Time: O(n \log n), $n = |a|+|b|$, $n = 2^{22}$ 约 1s
 */
#pragma once

struct cp{ // 复数 x+yi
	double x,y;
};
cp operator+(cp a,cp b){return {a.x+b.x,a.y+b.y};}
cp operator-(cp a,cp b){return {a.x-b.x,a.y-b.y};}
cp operator*(cp a,cp b){
	return {a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};
}
const double PI=acos(-1.0);
void fft(vector<cp>&f,int t){ // t=1 正变换, t=-1 逆变换
	int n=f.size();
	vector<int>rev(n); // 位逆序置换
	for(int i=1;i<n;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1)
			rev[i]|=n>>1;
	}
	for(int i=0;i<n;i++)
		if(i<rev[i])
			swap(f[i],f[rev[i]]);
	for(int len=1;len<n;len<<=1){
		vector<cp>w(len); // 单位根直接用 cos, sin 算, 精度高
		for(int j=0;j<len;j++)
			w[j]={cos(PI*j/len),t*sin(PI*j/len)};
		for(int i=0;i<n;i+=len<<1){
			for(int j=0;j<len;j++){
				cp u=f[i+j];
				cp v=w[j]*f[i+j+len];
				f[i+j]=u+v;
				f[i+j+len]=u-v;
			}
		}
	}
	if(t==-1){
		for(auto&z:f){
			z.x/=n;
			z.y/=n;
		}
	}
}
vector<ll>conv(const vector<ll>&a,const vector<ll>&b){
	if(a.empty()||b.empty())
		return {};
	int m=a.size()+b.size()-1;
	int n=1;
	while(n<m)
		n<<=1;
	vector<cp>f(n);
	for(int i=0;i<(int)a.size();i++)
		f[i].x=a[i];
	for(int i=0;i<(int)b.size();i++)
		f[i].y=b[i];
	fft(f,1);
	for(auto&z:f)
		z=z*z; // (a+bi)^2 的虚部为 2ab
	fft(f,-1);
	vector<ll>c(m);
	for(int i=0;i<m;i++)
		c[i]=llround(f[i].y/2);
	return c;
}
