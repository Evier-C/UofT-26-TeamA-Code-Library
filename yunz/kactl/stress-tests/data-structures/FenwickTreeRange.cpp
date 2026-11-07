#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/FenwickTree.h"

mt19937 rng(5);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

int main(){
	long long checks=0;
	for(int it=0;it<3000;it++){
		bool big=it>=2990;
		int n=big?rnd(100000,200000):rnd(1,50);
		rbit.init(n); // multi-test
		vector<ll>a(n+1);
		for(int s=0;s<(big?3000:200);s++){
			int l=rnd(1,n),r=rnd(l,n);
			if(big&&rng()%50)r=min(n,l+rnd(0,50));
			if(rng()%2){
				ll v=rnd(-1000000000,1000000000);
				rbit.rangeAdd(l,r,v);
				for(int i=l;i<=r;i++)a[i]+=v;
			}else{
				ll e=0;
				for(int i=l;i<=r;i++)e+=a[i];
				assert(rbit.rangeSum(l,r)==e);checks++;
			}
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
