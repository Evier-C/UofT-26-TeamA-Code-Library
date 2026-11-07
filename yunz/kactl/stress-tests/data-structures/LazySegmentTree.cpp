#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/LazySegmentTree.h"

mt19937 rng(9);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

int main(){
	long long checks=0;
	for(int it=0;it<3000;it++){
		int n=it<2990?rnd(1,50):rnd(1000,200000);
		int steps=it<2990?150:2000;
		vector<ll>b(n+1);
		for(int i=1;i<=n;i++)b[i]=a[i]=rnd(-1000,1000);
		build(1,1,n); // multi-test: rebuild over old garbage
		for(int s=0;s<steps;s++){
			int l=rnd(1,n),r=rnd(l,n);
			if(n>50&&rng()%100)r=min(n,l+rnd(0,30));
			if(rng()%2){
				ll v=rnd(-1000,1000);
				update(1,1,n,l,r,v);
				for(int i=l;i<=r;i++)b[i]+=v;
			}else{
				Node q=query(1,1,n,l,r);
				ll sm=0,mx=LLONG_MIN;
				for(int i=l;i<=r;i++)sm+=b[i],mx=max(mx,b[i]);
				assert(q.sum==sm&&q.mx==mx);
				checks++;
			}
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
