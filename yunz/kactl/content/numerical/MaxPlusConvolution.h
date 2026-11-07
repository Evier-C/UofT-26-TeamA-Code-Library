/**
 * Description: $(\max,+)$ 卷积 $c_k = \max_{i+j=k} (a_i + b_j)$, 其中 $b$ 是凹的
 * ($b_{j+1}-b_j$ 不增), $a$ 任意. 下标从 0 开始, 结果长度 $|a|+|b|-1$.
 * $b$ 凹时最优 $i$ 关于 $k$ 单调不降, 用分治 (决策单调性) 求解.
 * 求 $\min$ 卷积时要求 $b$ 是凸的: 全部取负即可.
 * Usage: vector<ll> c=maxPlus(a,b); // b 须为凹, a, b 非空
 * Time: O((|a|+|b|) \log (|a|+|b|))
 */
#pragma once

vector<ll>va,vb,vc;
// 求 c[l..r], 已知最优的 i 在 [optl, optr] 中
void mpdc(int l,int r,int optl,int optr){
	if(l>r)return;
	int mid=(l+r)/2,best=-1;
	int lo=max(optl,mid-(int)vb.size()+1);
	int hi=min({optr,mid,(int)va.size()-1});
	for(int i=lo;i<=hi;i++){ // 取最左的最优 i
		ll v=va[i]+vb[mid-i];
		if(best==-1||v>vc[mid])vc[mid]=v,best=i;
	}
	mpdc(l,mid-1,optl,best);
	mpdc(mid+1,r,best,optr);
}
vector<ll>maxPlus(const vector<ll>&a,const vector<ll>&b){
	va=a;vb=b;
	vc.assign(a.size()+b.size()-1,0);
	mpdc(0,(int)vc.size()-1,0,(int)a.size()-1);
	return vc;
}
