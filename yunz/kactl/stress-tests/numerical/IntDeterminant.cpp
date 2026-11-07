#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/IntDeterminant.h"

mt19937 rng(9);
ll leibniz(vector<vector<ll>>&m,ll p){
	int n=m.size();
	vector<int> q(n);
	iota(q.begin(),q.end(),0);
	ll res=0;
	do{
		int inv=0;
		for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(q[i]>q[j])inv++;
		ll t=1;
		for(int i=0;i<n;i++)t=t*(((m[i][q[i]])%p+p)%p)%p;
		res=(res+(inv&1?p-t:t))%p;
	}while(next_permutation(q.begin(),q.end()));
	return res%p;
}
ll pw(ll b,ll e,ll p){ll r=1%p;for(b%=p;e;e>>=1,b=b*b%p)if(e&1)r=r*b%p;return r;}
// 模素数, 用逆元消元
ll detPrime(vector<vector<ll>> m,ll p){
	int n=m.size();ll res=1;
	for(auto&r:m)for(auto&v:r)v=(v%p+p)%p;
	for(int i=0;i<n;i++){
		int q=-1;
		for(int j=i;j<n;j++)if(m[j][i]){q=j;break;}
		if(q<0)return 0;
		if(q!=i)swap(m[q],m[i]),res=(p-res)%p;
		res=res*m[i][i]%p;
		ll iv=pw(m[i][i],p-2,p);
		for(int j=i+1;j<n;j++){
			ll t=m[j][i]*iv%p;
			for(int k=i;k<n;k++)m[j][k]=(m[j][k]-t*m[i][k]%p+p)%p;
		}
	}
	return res;
}
void load(vector<vector<ll>>&m){
	int n=m.size();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=m[i-1][j-1];
}
int main(){
	long long checks=0;
	vector<ll> mods={1,2,3,4,6,7,8,12,30,97,100,1000,65536,998244353,1000000007};
	for(int it=0;it<20000;it++){
		int n=rng()%6+1;
		ll p=mods[rng()%mods.size()];
		vector<vector<ll>> m(n,vector<ll>(n));
		ll R=rng()%2?3:(ll)2e9;
		for(auto&r:m)for(auto&v:r)v=(ll)(rng()%(2*R+1))-R;
		if(n>1&&rng()%4==0)m[rng()%n]=m[rng()%n];
		load(m);
		ll got=detMod(n,p);
		assert(got==leibniz(m,p));
		assert(0<=got&&got<p);
		checks++;
	}
	// 大矩阵: 素数模与逆元消元比较; 合数模 p1*p2 用 CRT 比较
	for(int it=0;it<60;it++){
		int n=rng()%150+1;
		ll p1=10007,p2=10009,p=p1*p2;
		vector<vector<ll>> m(n,vector<ll>(n));
		for(auto&r:m)for(auto&v:r)v=rng()%p;
		if(rng()%3==0)m[rng()%n]=m[rng()%n];
		load(m);
		ll got=detMod(n,998244353);
		assert(got==detPrime(m,998244353));
		load(m);
		got=detMod(n,p);
		ll d1=detPrime(m,p1),d2=detPrime(m,p2);
		assert(got%p1==d1&&got%p2==d2);
		checks+=2;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
