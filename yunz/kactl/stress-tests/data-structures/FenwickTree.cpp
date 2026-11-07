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
		n=big?rnd(100000,200000):rnd(1,50);
		for(int i=1;i<=n;i++)c[i]=0; // multi-test clear
		vector<ll>a(n+1);
		for(int s=0;s<(big?3000:200);s++){
			int op=rng()%3;
			if(op==0){
				int x=rnd(1,n);ll v=rnd(0,1000);
				add(x,v);a[x]+=v;
			}else if(op==1){
				int l=rnd(1,n),r=rnd(l,n);
				if(big)r=min(n,l+rnd(0,50));
				ll e=0;
				for(int i=l;i<=r;i++)e+=a[i];
				assert(ask(r)-ask(l-1)==e);checks++;
			}else if(!big||s%100==0){
				ll tot=0;
				for(int i=1;i<=n;i++)tot+=a[i];
				ll sv=rnd(-5,(int)tot+5);
				int e=1;ll pre=0;
				while(e<=n&&pre+a[e]<sv)pre+=a[e],e++;
				if(sv<=0)e=1;
				assert(search(sv)==e);checks++;
			}
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
