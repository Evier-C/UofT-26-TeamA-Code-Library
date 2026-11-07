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

// number of connected components of adjacency list graph on nodes 1..k
int forestComps(vector<int>*adj,int k,vector<int>&lab){
	lab.assign(k+1,0);int c=0;
	for(int s=1;s<=k;s++)if(!lab[s]){
		c++;vector<int> st={s};lab[s]=c;
		while(!st.empty()){int u=st.back();st.pop_back();
			for(int v:adj[u])if(!lab[v])lab[v]=c,st.push_back(v);}
	}
	return c;
}

int main(){
	long long checks=0;
	for(int it=0;it<6000;it++){
		n=R(1,7);m=R(0,12);
		if(it%4==0)m=R(0,n);
		B.init(n,m);E.clear();
		for(int i=1;i<=m;i++){
			int u=R(1,n),v=R(1,n);
			if(R(0,5)&&u==v)v=u%n+1;
			E.push_back({u,v});
			B.g[u].push_back({v,i}),B.g[v].push_back({u,i});
		}
		for(int i=1;i<=n;i++)if(!B.dfn[i])B.tarjan(i,0,i);
		int all=((1<<(n+1))-2);
		vector<int> lab,lab2;
		int c0=comps(all,-1,lab);
		// B.cut vertices
		for(int x=1;x<=n;x++){
			int c=comps(all^(1<<x),-1,lab2);
			bool isolated=true;
			for(auto[a,b]:E)if((a==x)!=(b==x))isolated=false;
			bool exp=c>c0-(isolated?1:0);
			assert(B.cut[x]==exp);checks++;
		}
		// bridges
		for(int i=1;i<=m;i++){
			int c=comps(all,i,lab2);
			assert(B.bri[i]==(c>c0));checks++;
		}
		// 2-edge-connected components: same iff connected without bridges
		{
			vector<int> l;
			// remove all bridges
			vector<array<int,2>> keep=E;
			auto E0=E;E.clear();
			for(int i=1;i<=m;i++)if(!B.bri[i])E.push_back(E0[i-1]);
			int m0=m;m=E.size();
			comps(all,-1,l);
			E=E0;m=m0;
			for(int u=1;u<=n;u++)for(int v=1;v<=n;v++){
				assert((B.eb[u]==B.eb[v])==(l[u]==l[v]));checks++;
			}
			for(int u=1;u<=n;u++)assert(B.eb[u]>=1&&B.eb[u]<=B.ec);
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
			for(int i=1;i<=B.vc;i++){
				auto v=B.vb[i];sort(v.begin(),v.end());
				assert(!got.count(v));got.insert(v);
			}
			assert(exp==got);checks++;
		}
		// round-square tree
		{
			B.buildRS(n);
			int K=n+B.vc;long long de=0;
			for(int i=1;i<=K;i++)de+=B.T[i].size();
			assert(de%2==0);
			long long ed=de/2,sum=0;
			for(int i=1;i<=B.vc;i++)sum+=B.vb[i].size();
			assert(ed==sum);
			vector<int> rl;
			int rc=forestComps(B.T,K,rl);
			assert(ed==K-rc); // forest
			for(int i=1;i<=B.vc;i++){
				auto a=B.T[n+i],b=B.vb[i];
				sort(a.begin(),a.end());sort(b.begin(),b.end());
				assert(a==b);
				for(int x:a)assert(x>=1&&x<=n);
			}
			for(int x=1;x<=n;x++)for(int y:B.T[x])assert(y>n&&y<=K);
			for(int u=1;u<=n;u++)for(int v=1;v<=n;v++)
				assert((lab[u]==lab[v])==(rl[u]==rl[v])),checks++;
			for(int x=1;x<=n;x++){
				bool isolated=true;
				for(auto[a,b]:E)if((a==x)!=(b==x))isolated=false;
				if(isolated)assert(B.T[x].size()==1&&!B.cut[x]);
				else assert(B.cut[x]==(B.T[x].size()>=2));
				checks++;
			}
		}
		// bridge tree
		{
			B.buildBT(n);
			long long de=0;
			multiset<pair<int,int>> ge,ee;
			for(int i=1;i<=B.ec;i++)for(int j:B.E2[i]){
				assert(j>=1&&j<=B.ec&&j!=i);de++;ge.insert({i,j});
			}
			int nb=0;
			for(int i=1;i<=m;i++)if(B.bri[i]){
				nb++;auto[a,b]=E[i-1];
				ee.insert({B.eb[a],B.eb[b]});ee.insert({B.eb[b],B.eb[a]});
			}
			assert(ge==ee&&de==2*nb);
			vector<int> bl;
			int bc=forestComps(B.E2,B.ec,bl);
			assert(nb==B.ec-bc); // forest
			// same component of graph iff same component of bridge tree
			for(int u=1;u<=n;u++)for(int v=1;v<=n;v++)
				assert((lab[u]==lab[v])==(bl[B.eb[u]]==bl[B.eb[v]]));
			checks++;
		}
	}
	// large: path graph + extra, just run for crashes and sanity
	{
		n=5000;m=n-1;B.init(n,m);
		for(int i=1;i<n;i++)B.g[i].push_back({i+1,i}),B.g[i+1].push_back({i,i});
		for(int i=1;i<=n;i++)if(!B.dfn[i])B.tarjan(i,0,i);
		assert(B.vc==n-1&&B.ec==n);
		for(int i=1;i<=m;i++)assert(B.bri[i]);
		for(int i=1;i<=n;i++)assert(B.cut[i]==(i!=1&&i!=n));
		B.buildRS(n);B.buildBT(n);
		for(int i=1;i<=n;i++)assert((int)B.T[i].size()==((i!=1&&i!=n)?2:1));
		long long de=0;for(int i=1;i<=B.ec;i++)de+=B.E2[i].size();
		assert(de==2*(n-1));
		checks++;
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
