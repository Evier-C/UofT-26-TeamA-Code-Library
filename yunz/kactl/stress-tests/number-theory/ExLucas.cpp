#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/ExLucas.h"

int main(){
	mt19937 rng(17);
	ll checks=0;
	int N=200;
	auto pascal=[&](ll P){
		vector<vector<ll>>C(N+1,vector<ll>(N+1,0));
		for(int n=0;n<=N;n++){
			C[n][0]=1%P;
			for(int m=1;m<=n;m++)C[n][m]=(C[n-1][m-1]+C[n-1][m])%P;
		}
		return C;
	};
	vector<ll>small={1,2,4,8,3,9,27,6,12,36,100,360,1000,30030,1024,729};
	for(ll P:small){
		auto C=pascal(P);
		for(int n=0;n<=N;n++)for(int m=-2;m<=n+2;m++){
			ll want=(m<0||m>n)?0:C[n][m];
			assert(exlucas(n,m,P)==want);checks++;
		}
	}
	vector<ll>big={99991,65536,59049,362880,1000000,999983};
	for(int i=0;i<14;i++)big.push_back(1+(ll)(rng()%1000000));
	for(ll P:big){
		auto C=pascal(P);
		for(int k=0;k<40;k++){
			int n=rng()%(N+1),m=rng()%(n+1);
			assert(exlucas(n,m,P)==C[n][m]);checks++;
		}
	}
	// 大 n, 质数模数: 与 Lucas 定理比较
	for(ll p:{3LL,7LL,1009LL})for(int it=0;it<300;it++){
		ll n=rng()*(ll)rng()%1000000000000000000LL,m=rng()*(ll)rng()%(n+1);
		ll want=1,nn=n,mm=m;
		auto Cs=[&](ll a,ll b){ // a, b < p
			if(b>a)return 0LL;
			ll r=1;
			for(ll i=0;i<b;i++)r=r*((a-i)%p)%p*pw(i+1,p-2,p)%p;
			return r;
		};
		while(nn||mm)want=want*Cs(nn%p,mm%p)%p,nn/=p,mm/=p;
		assert(exlucas(n,m,p)==want);checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
