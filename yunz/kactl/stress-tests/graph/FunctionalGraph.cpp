#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/FunctionalGraph.h"

mt19937 rng(31);
int R(int a,int b){return rng()%(b-a+1)+a;}

int main(){
	long long checks=0;
	for(int it=0;it<20000;it++){
		bool big=it>=19995;
		int n=big?200000:R(1,10);
		for(int i=1;i<=n;i++)a[i]=R(1,n);
		if(big&&it%2)for(int i=1;i<=n;i++)a[i]=i<n?i+1:R(1,n);
		solve(n);
		// on cycle: a^k(x)==x for some k in [1,n]
		vector<int> on(n+1);
		if(!big){
			for(int x=1;x<=n;x++){int y=x;for(int k=0;k<n;k++){y=a[y];if(y==x){on[x]=1;break;}}}
		}else{
			// mark via cycle arrays and verify ring structure below
			for(int k=1;k<=cnt;k++)for(int x:cyc[k])on[x]=1;
		}
		vector<int> seen(n+1);
		for(int k=1;k<=cnt;k++){
			int L=cyc[k].size();assert(L>0);
			for(int j=0;j<L;j++){
				int x=cyc[k][j];assert(on[x]&&!seen[x]);seen[x]=1;
				assert(a[x]==cyc[k][(j+1)%L]);
				assert(bel[x]==k&&pos[x]==j&&rt[x]==x&&dep[x]==0);
			}
		}
		for(int x=1;x<=n;x++){
			assert(seen[x]==on[x]);
			if(!big){
				int y=x,d=0;while(!on[y])y=a[y],d++;
				assert(rt[x]==y&&dep[x]==d&&bel[x]==bel[y]&&pos[x]==pos[y]);
				// k steps
				int L=cyc[bel[x]].size();
				int z=x;
				for(int k=0;k<3*n;k++){
					if(k>=dep[x])assert(z==cyc[bel[x]][(pos[x]+k-dep[x])%L]);
					z=a[z];
				}
			}else{
				if(!on[x])assert(dep[x]==dep[a[x]]+1&&rt[x]==rt[a[x]]);
			}
			checks++;
		}
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
