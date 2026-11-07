#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/BiconnectedComponents.h"

mt19937 rng(17);
int R(int a,int b){return rng()%(b-a+1)+a;}

int n,m;
vector<array<int,2>> E;
// components ignoring vertex skipV (mask) and edge skipE
int comps(int maskV,int skipE,vector<int>&lab){
	lab.assign(n+1,0);int c=0;
	for(int s=1;s<=n;s++)if((maskV>>s&1)&&!lab[s]){
		c++;vector<int> st={s};lab[s]=c;
		while(!st.empty()){int u=st.back();st.pop_back();
			for(int i=0;i<m;i++)if(i+1!=skipE){
				auto[a,b]=E[i];
				if(!(maskV>>a&1)||!(maskV>>b&1))continue;
				int w=a==u?b:b==u?a:0;
				if(w&&!lab[w])lab[w]=c,st.push_back(w);
			}
		}
	}
	return c;
}
bool biconn(int mask){ // induced subgraph on mask is a block?
	int k=__builtin_popcount(mask);
	vector<int> lab;
	if(k==1)return true;
	if(comps(mask,-1,lab)!=1)return false;
	if(k==2)return true;
	for(int x=1;x<=n;x++)if(mask>>x&1)
		if(comps(mask^(1<<x),-1,lab)!=1)return false;
	return true;
}

int main(){
	long long checks=0;
	for(int it=0;it<6000;it++){
		n=R(1,7);m=R(0,12);
		if(it%4==0)m=R(0,n);
		init(n,m);E.clear();
		for(int i=1;i<=m;i++){
			int u=R(1,n),v=R(1,n);
			if(R(0,5)&&u==v)v=u%n+1;
			E.push_back({u,v});
			g[u].push_back({v,i}),g[v].push_back({u,i});
		}
		for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i,0,i);
		int all=((1<<(n+1))-2);
		vector<int> lab,lab2;
		int c0=comps(all,-1,lab);
		// cut vertices
		for(int x=1;x<=n;x++){
			int c=comps(all^(1<<x),-1,lab2);
			bool isolated=true;
			for(auto[a,b]:E)if((a==x)!=(b==x))isolated=false;
			bool exp=c>c0-(isolated?1:0);
			assert(cut[x]==exp);checks++;
		}
		// bridges
		for(int i=1;i<=m;i++){
			int c=comps(all,i,lab2);
			assert(bri[i]==(c>c0));checks++;
		}
		// 2-edge-connected components: same iff connected without bridges
		{
			vector<int> l;
			// remove all bridges
			vector<array<int,2>> keep=E;
			auto E0=E;E.clear();
			for(int i=1;i<=m;i++)if(!bri[i])E.push_back(E0[i-1]);
			int m0=m;m=E.size();
			comps(all,-1,l);
			E=E0;m=m0;
			for(int u=1;u<=n;u++)for(int v=1;v<=n;v++){
				assert((eb[u]==eb[v])==(l[u]==l[v]));checks++;
			}
			for(int u=1;u<=n;u++)assert(eb[u]>=1&&eb[u]<=ec);
		}
		// vertex BCC: maximal biconnected vertex sets
		{
			vector<int> good(1<<(n+1));
			for(int mask=2;mask<=all;mask+=2)good[mask]=biconn(mask);
			set<vector<int>> exp,got;
			for(int mask=2;mask<=all;mask+=2)if(good[mask]){
				bool mx=true;
				for(int sup=2;sup<=all;sup+=2)if(sup!=mask&&(sup&mask)==mask&&good[sup])mx=false;
				if(mx){vector<int> v;for(int x=1;x<=n;x++)if(mask>>x&1)v.push_back(x);exp.insert(v);}
			}
			for(int i=1;i<=vc;i++){
				auto v=vb[i];sort(v.begin(),v.end());
				assert(!got.count(v));got.insert(v);
			}
			assert(exp==got);checks++;
		}
	}
	// large: path graph + extra, just run for crashes and sanity
	{
		n=5000;m=n-1;init(n,m);
		for(int i=1;i<n;i++)g[i].push_back({i+1,i}),g[i+1].push_back({i,i});
		for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i,0,i);
		assert(vc==n-1&&ec==n);
		for(int i=1;i<=m;i++)assert(bri[i]);
		for(int i=1;i<=n;i++)assert(cut[i]==(i!=1&&i!=n));
		checks++;
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
