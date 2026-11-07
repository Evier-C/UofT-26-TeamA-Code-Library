#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/ModMulLL.h"

typedef unsigned long long ull;
ll slowMul(ull a,ull b,ull m){ // 加倍法
	ull r=0;a%=m;
	for(;b;b>>=1){
		if(b&1)r=(r>=m-a)?r-(m-a):r+a;
		a=(a>=m-a)?a-(m-a):a+a;
	}
	return r;
}
int main(){
	mt19937_64 rng(4);
	ll checks=0;
	for(int it=0;it<1000000;it++){
		int k=rng()%63+1;
		ll m=(ll)(rng()>>(64-k))|1;
		if(it%3==0)m=LLONG_MAX-(ll)(rng()%1000);
		ll a=rng()%m,b=rng()%m;
		assert(mulmod(a,b,m)==slowMul(a,b,m));checks++;
	}
	for(int it=0;it<20000;it++){
		ll m=rng()%LLONG_MAX+1,a=rng()%m;int b=rng()%30;
		ll want=1%m;
		for(int i=0;i<b;i++)want=slowMul(want,a,m);
		assert(powmod(a,b,m)==want);checks++;
	}
	ll p=(1LL<<61)-1; // 质数
	for(int it=0;it<1000;it++){
		ll a=rng()%(p-1)+1;
		assert(powmod(a,p-1,p)==1);checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
