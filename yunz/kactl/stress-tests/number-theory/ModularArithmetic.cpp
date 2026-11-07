#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/ModularArithmetic.h"

int main(){
	mt19937_64 rng(1);
	ll checks=0;
	for(int rep=0;rep<2;rep++){ // init 可以重复调用
		int n=rep?2000:300;
		init(n);
		vector<vector<ll>>c(n+1,vector<ll>(n+2,0));
		for(int i=0;i<=n;i++){
			c[i][0]=1;
			for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j-1]+(j<i?c[i-1][j]:0))%MOD;
		}
		for(int i=0;i<=n;i++)for(int j=-2;j<=i+2;j++){
			ll want=(j<0||j>i)?0:c[i][j];
			assert(C(i,j)==want);checks++;
		}
	}
	init(1000000);
	for(int i=0;i<=1000000;i+=997)
		assert(fac[i]*ifac[i]%MOD==1),checks++;
	for(int it=0;it<100000;it++){
		ll a=(ll)(rng()%(4*MOD))-2*MOD;
		ll b=rng()%50;
		ll want=1,am=(a%MOD+MOD)%MOD;
		for(int i=0;i<b;i++)want=want*am%MOD;
		assert(qpow(a,b)==want);checks++;
		if(am)assert(inv(a)*am%MOD==1),checks++;
	}
	assert(qpow(3,MOD-1)==1);
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
