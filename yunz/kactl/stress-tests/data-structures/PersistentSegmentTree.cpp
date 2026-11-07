#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/PersistentSegmentTree.h"

mt19937 rng(12345);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

int main(){
	long long checks=0;
	// 1) point add on random old versions, range sum
	for(int it=0;it<3000;it++){
		pst.tot=0; // multi-test
		int n=rnd(1,40);
		vector<int>root={0};
		vector<vector<ll>>arr={vector<ll>(n+1,0)};
		for(int s=0;s<60;s++){
			int base=rnd(0,(int)root.size()-1),x=rnd(1,n);
			ll v=rnd(-1000000,1000000);
			root.push_back(pst.update(root[base],1,n,x,v));
			arr.push_back(arr[base]);arr.back()[x]+=v;
			int q=rnd(0,(int)root.size()-1),l=rnd(1,n),r=rnd(l,n);
			ll e=0;
			for(int i=l;i<=r;i++)e+=arr[q][i];
			assert(pst.query(root[q],1,n,l,r)==e);checks++;
		}
	}
	// 2) pst.kth smallest in a[l..r], as in Usage
	for(int it=0;it<500;it++){
		pst.tot=0;
		bool big=it>=495;
		int n=big?200000:rnd(1,40);
		vector<int>a(n+1),b;
		for(int i=1;i<=n;i++)a[i]=rnd(-50,big?1000000000:50),b.push_back(a[i]);
		sort(b.begin(),b.end());b.erase(unique(b.begin(),b.end()),b.end());
		int m=(int)b.size();
		b.insert(b.begin(),0); // b[1..m]
		auto id=[&](int x){return int(lower_bound(b.begin()+1,b.end(),x)-b.begin());};
		for(int i=1;i<=n;i++)pst.rt[i]=pst.update(pst.rt[i-1],1,m,id(a[i]),1);
		assert(pst.tot<pst.MX);
		for(int q=0;q<(big?2000:100);q++){
			int l=rnd(1,n),r=big?min(n,l+rnd(0,50)):rnd(l,n);
			vector<int>c(a.begin()+l,a.begin()+r+1);
			sort(c.begin(),c.end());
			int k=rnd(1,r-l+1);
			assert(b[pst.kth(pst.rt[l-1],pst.rt[r],1,m,k)]==c[k-1]);checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
