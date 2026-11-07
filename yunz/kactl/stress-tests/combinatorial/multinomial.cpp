#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/combinatorial/multinomial.h"

mt19937 rng(5);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

int main(){
	long long checks=0;
	assert(multinomial({2,1,1})==12);
	assert(multinomial({})==1);
	// brute: product of binomials via Pascal triangle (__int128 overflow guard)
	static __int128 C[70][70];
	for(int i=0;i<70;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	for(int it=0;it<200000;it++){
		int cnt=rnd(0,6);
		vector<int>k(cnt);
		for(int&x:k)x=rnd(0,it%2?20:8);
		__int128 e=1;int m=0;bool ok=1;
		for(int x:k){
			m+=x;
			if(m>=70){ok=0;break;}
			e*=C[m][x];
			if(e>(__int128)1e15){ok=0;break;}
		}
		if(!ok)continue;
		assert(multinomial(k)==(ll)e);checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
