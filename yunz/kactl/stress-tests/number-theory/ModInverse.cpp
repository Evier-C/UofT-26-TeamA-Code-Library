#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/ModInverse.h"

int main(){
	ll checks=0;
	vector<ll>ps={2,3,5,7,11,13,97,101,1009,7919,65537};
	for(ll p:ps){
		int n=(int)p-1;
		initInv(n,p);
		for(int i=1;i<=n;i++)assert(i*inv[i]%p==1),checks++;
	}
	for(ll p:{1000000007LL,998244353LL}){
		initInv(1000000,p);
		for(int i=1;i<=1000000;i++)assert(i*inv[i]%p==1),checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
