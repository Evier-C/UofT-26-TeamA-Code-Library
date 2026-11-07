#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/AllRoots.h"

mt19937 rng(11);
int R(int a,int b){return rng()%(b-a+1)+a;}

int main(){
	long long checks=0;
	for(int it=0;it<3000;it++){
		bool big=it>=2995;
		n=big?R(1000,3000):R(1,12);
		for(int i=1;i<=n;i++)g[i].clear();
		vector<int> perm(n+1);iota(perm.begin(),perm.end(),0);
		shuffle(perm.begin()+1,perm.end(),rng);
		for(int i=2;i<=n;i++){
			int p=it%3==0?i-1:R(1,i-1),w=R(0,1000000000);
			int u=perm[i],v=perm[p];
			g[u].push_back({v,w}),g[v].push_back({u,w});
		}
		dfs1(1,0);ans[1]=f[1];up[1]=0;dfs2(1,0);
		for(int u=1;u<=n;u++)far[u]=max(d1[u],up[u]);
		for(int s=1;s<=n;s++){
			vector<ll> dist(n+1,-1);dist[s]=0;
			vector<int> st={s};
			while(!st.empty()){int u=st.back();st.pop_back();
				for(auto[v,w]:g[u])if(dist[v]<0)dist[v]=dist[u]+w,st.push_back(v);}
			ll sum=0,mx=0;
			for(int v=1;v<=n;v++)sum+=dist[v],mx=max(mx,dist[v]);
			assert(ans[s]==sum&&far[s]==mx);checks++;
		}
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
