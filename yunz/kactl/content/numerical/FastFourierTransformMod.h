/**
 * Description: 任意模数多项式乘法 (拆系数 FFT, 共 4 次 FFT, 用 FastFourierTransform.h
 * 的 cp 和 fft). \texttt{convMod(a, b)}: 输入两个 vector<ll>, 下标从 0 开始,
 * 值必须在 $[0, MOD)$ 内; 返回 $c_k = \sum_{i+j=k} a_i b_j \bmod MOD$,
 * 长度 $|a|+|b|-1$. MOD 改成题目的模数 (任意正整数, 须 $< 2^{30}$, 不必是素数).
 * 做法: 拆 $a = a_1 2^{15} + a_0$, $b$ 同理; 令 $P = a_1 + i a_0$, $Q = b_1 + i b_0$,
 * 由 $P$ 的共轭对称分离出 $a_1, a_0$ 的 DFT, 再算 $X = A_1 Q$, $Y = A_0 Q$,
 * 逆变换后实部虚部分别为 $a_1b_1, a_1b_0, a_0b_1, a_0b_0$, 合并取模.
 * 精度: $n \log_2 n \cdot MOD < 8.6 \cdot 10^{14}$ 时安全, 实际 $n = 10^6$,
 * MOD $= 10^9+7$ 没问题.
 * Usage: vector<ll> a={1,2},b={3,MOD-1}; // 系数在 [0,MOD)
 * vector<ll> c=convMod(a,b); // c[k]=sum a[i]b[k-i] mod MOD
 * Time: O(n \log n), $n = |a|+|b|$, 约为普通 FFT 的两倍
 */
#pragma once

#include "FastFourierTransform.h"

const ll MOD=1000000007; // 模数, 按题目修改
vector<ll>convMod(const vector<ll>&a,const vector<ll>&b){
	if(a.empty()||b.empty())
		return {};
	int m=a.size()+b.size()-1;
	int n=1;
	while(n<m)
		n<<=1;
	vector<cp>P(n),Q(n),X(n),Y(n);
	// P = a1 + i a0, Q = b1 + i b0
	for(int i=0;i<(int)a.size();i++)
		P[i]={double(a[i]>>15),double(a[i]&32767)};
	for(int i=0;i<(int)b.size();i++)
		Q[i]={double(b[i]>>15),double(b[i]&32767)};
	fft(P,1);
	fft(Q,1);
	for(int i=0;i<n;i++){
		int j=(n-i)&(n-1);
		cp cj={P[j].x,-P[j].y}; // P[n-i] 的共轭
		cp s=P[i]+cj; // 2 FFT(a1)
		cp d=P[i]-cj; // 2i FFT(a0)
		cp A1={s.x/2,s.y/2};
		cp A0={d.y/2,-d.x/2};
		X[i]=A1*Q[i];
		Y[i]=A0*Q[i];
	}
	fft(X,-1);
	fft(Y,-1);
	// X = a1b1 + i a1b0, Y = a0b1 + i a0b0
	vector<ll>c(m);
	for(int i=0;i<m;i++){
		ll v11=llround(X[i].x)%MOD;
		ll v10=llround(X[i].y)%MOD;
		ll v01=llround(Y[i].x)%MOD;
		ll v00=llround(Y[i].y)%MOD;
		c[i]=((v11<<30)%MOD+((v10+v01)<<15)+v00)%MOD;
	}
	return c;
}
