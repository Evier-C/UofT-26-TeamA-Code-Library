#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/BerlekampMassey.h"

mt19937 rng(3);
int main(){
	long long checks=0;
	assert((BM({0,1,1,3,5,11})==vector<ll>{1,2}));
	assert(BM({}).empty());
	assert(BM({0,0,0,0}).empty());
	checks+=3;
	for(int it=0;it<20000;it++){
		int L=rng()%8; // 递推阶数
		vector<ll> tr(L);
		for(auto&v:tr)v=(rng()%3==0)?rng()%MOD:rng()%5;
		int len=2*L+(int)(rng()%5);
		vector<ll> s(len);
		for(int i=0;i<len;i++){
			if(i<L)s[i]=(rng()%2)?rng()%MOD:rng()%5;
			else{
				s[i]=0;
				for(int j=0;j<L;j++)s[i]=(s[i]+tr[j]*s[i-j-1])%MOD;
			}
		}
		vector<ll> C=BM(s);
		int r=C.size();
		// C 必须生成整个序列, 且阶数不超过 L
		assert(r<=L);
		for(int i=r;i<len;i++){
			ll v=0;
			for(int j=0;j<r;j++)v=(v+C[j]*s[i-j-1])%MOD;
			assert(v==s[i]);
		}
		for(ll v:C)assert(0<=v&&v<MOD);
		checks++;
	}
	// 最短性: 不存在更短的递推式
	for(int it=0;it<3000;it++){
		int len=rng()%9+1;
		vector<ll> s(len);
		for(auto&v:s)v=rng()%3;
		vector<ll> C=BM(s);
		int r=C.size();
		for(int i=r;i<len;i++){
			ll v=0;
			for(int j=0;j<r;j++)v=(v+C[j]*s[i-j-1])%MOD;
			assert(v==s[i]);
		}
		// 阶数 r-1 的递推不存在: 线性方程组无解 (模素数高斯消元)
		if(r>0){
			int q=r-1,eq=len-q;
			vector<vector<ll>> M(eq,vector<ll>(q+1));
			for(int i=q;i<len;i++){
				for(int j=0;j<q;j++)M[i-q][j]=s[i-j-1];
				M[i-q][q]=s[i];
			}
			int row=0;
			for(int c=0;c<=q&&row<eq;c++){
				int p=-1;
				for(int i=row;i<eq;i++)if(M[i][c]){p=i;break;}
				if(p<0)continue;
				swap(M[p],M[row]);
				ll inv=qpow(M[row][c],MOD-2);
				for(int i=0;i<eq;i++)if(i!=row&&M[i][c]){
					ll t=M[i][c]*inv%MOD;
					for(int j=0;j<=q;j++)
						M[i][j]=(M[i][j]-t*M[row][j]%MOD+MOD)%MOD;
				}
				if(c==q){row=-1;break;} // 常数列为主元: 无解
				row++;
			}
			assert(row==-1);
		}
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
