#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/XorBasis.h"

// 所有非空子集的异或值 (去重, 排序)
vector<ll>allXor(vector<ll>v){
	set<ll>s;
	int n=v.size();
	for(int m=1;m<(1<<n);m++){
		ll x=0;
		for(int i=0;i<n;i++)if(m>>i&1)x^=v[i];
		s.insert(x);
	}
	return vector<ll>(s.begin(),s.end());
}
int a[505];
int main(){
	mt19937_64 rng(21);
	ll checks=0;
	// 整体线性基, 小数据暴力
	for(int it=0;it<20000;it++){
		int n=rng()%11;
		int bits=rng()%6+1;
		if(it%5==0)bits=62;
		xb.init();
		vector<ll>v;
		set<ll>span={0};
		bool zero=0;
		for(int i=0;i<n;i++){
			ll x=rng()&((1LL<<bits)-1);
			if(bits==62&&i>=3&&rng()%2)x=v[0]^v[1]^v[2]; // 制造相关
			bool rep=span.count(x);
			bool ind=xb.insert(x);
			assert(ind==!rep);
			if(rep)zero=1;
			set<ll>ns=span;
			for(ll y:span)ns.insert(y^x);
			span=ns;
			v.push_back(x);
		}
		vector<ll>all=allXor(v);
		assert((xb.cnt>xb.rk)==zero);
		assert(zero==(n>0&&all[0]==0));
		assert((ll)span.size()==(1LL<<xb.rk));
		ll mx=0;
		for(ll x:span)mx=max(mx,x);
		assert(xb.qmax()==mx);
		assert(xb.qmin()==(n?all[0]:-1));
		for(int t=0;t<30;t++){
			ll x=rng()&((1LL<<bits)-1);
			if(t<10&&!all.empty())x=all[rng()%all.size()];
			assert(xb.check(x)==(span.count(x)>0));
		}
		assert(xb.check(0));
		xb.rebuild();
		assert(xb.qmax()==mx);
		vector<ll>sp(span.begin(),span.end()); // 含 0, 允许空集
		vector<ll>nz; // 不含 0
		for(ll x:sp)if(x)nz.push_back(x);
		int lim=min<ll>(sp.size()+2,200);
		for(int k=1;k<=lim;k++){
			ll w=k<=(int)sp.size()?sp[k-1]:-1;
			assert(xb.kth(k,true)==w);
			ll u=k<=(int)all.size()?all[k-1]:-1;
			assert(xb.kth(k,xb.cnt>xb.rk)==u);
			ll q=k<=(int)nz.size()?nz[k-1]:-1;
			assert(xb.kth(k,false)==q);
			checks+=3;
		}
		// rebuild 后再插入, 再 rebuild
		ll x=rng()&((1LL<<bits)-1);
		xb.insert(x);
		xb.rebuild();
		set<ll>ns=span;
		for(ll y:span)ns.insert(y^x);
		vector<ll>s2(ns.begin(),ns.end());
		for(int k=1;k<=min<int>(s2.size(),50);k++)assert(xb.kth(k,true)==s2[k-1]);
		checks++;
	}
	// 满秩 63 位时 kth 不溢出
	xb.init();
	for(int i=0;i<63;i++)xb.insert(1LL<<i);
	xb.rebuild();
	assert(xb.kth(1,false)==1&&xb.kth(LLONG_MAX,false)==LLONG_MAX);
	assert(xb.kth(LLONG_MAX,true)==LLONG_MAX-1);
	assert(xb.qmax()==LLONG_MAX&&xb.qmin()==1);
	// 区间线性基, 多组数据
	for(int it=0;it<300;it++){
		int n=rng()%40+1;
		int bits=rng()%8+1;
		if(it%3==0)bits=30;
		rb.init();
		for(int i=1;i<=n;i++){
			a[i]=rng()&((1<<bits)-1);
			if(bits==30&&i>2&&rng()%3==0)a[i]=a[i-1]^a[i-2];
			rb.add(a[i]);
		}
		for(int l=1;l<=n;l++){
			vector<int>bs; // 暴力的基, 从大到小
			for(int r=l;r<=n;r++){
				int x=a[r];
				for(int y:bs)x=min(x,x^y);
				if(x){
					bs.push_back(x);
					sort(bs.rbegin(),bs.rend());
				}
				int mx=0;
				for(int y:bs)mx=max(mx,mx^y);
				assert(rb.rank(l,r)==(int)bs.size());
				assert(rb.qmax(l,r)==mx);
				for(int t=0;t<5;t++){
					int x=rng()&((1<<bits)-1);
					if(t==0)x=a[l+rng()%(r-l+1)]^a[l+rng()%(r-l+1)];
					int y=x;
					for(int z:bs)y=min(y,y^z);
					assert(rb.check(l,r,x)==(y==0));
				}
				// 非空子集异或出 0
				bool z=r-l+1>rb.rank(l,r);
				if(r-l+1<=12){
					vector<ll>v(a+l,a+r+1);
					assert(z==(allXor(v)[0]==0));
				}
				checks++;
			}
		}
	}
	// 大数据
	rb.init();
	int n=500000;
	for(int i=1;i<=n;i++)rb.add(rng()&((1u<<31)-1));
	for(int t=0;t<1000;t++){
		int l=rng()%n+1,r=rng()%n+1;
		if(l>r)swap(l,r);
		if(r-l>100)assert(rb.rank(l,r)==31);
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
