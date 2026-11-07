#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/TopoSort.h"

mt19937 rng(7);
int R(int a,int b){return rng()%(b-a+1)+a;}

int main(){
	int checks=0;
	for(int it=0;it<20000;it++){
		int n=it<19990?R(1,9):R(1000,200000),m=it<19990?R(0,15):R(0,300000);
		bool dag=R(0,1);
		vector<int> perm(n+1);iota(perm.begin(),perm.end(),0);
		shuffle(perm.begin()+1,perm.end(),rng);
		for(int i=1;i<=n;i++)g[i].clear();
		vector<pair<int,int>> E;
		for(int i=0;i<m;i++){
			int a=R(1,n),b=R(1,n);
			if(dag){if(a==b)continue;if(a>b)swap(a,b);}
			E.push_back({perm[a],perm[b]});
			g[perm[a]].push_back(perm[b]);
		}
		bool res=topo(n);
		// brute: cycle exists? repeatedly remove sources
		vector<int> indeg(n+1),alive(n+1,1);
		for(auto[a,b]:E)indeg[b]++;
		int removed=0;
		vector<int> st;
		for(int i=1;i<=n;i++)if(!indeg[i])st.push_back(i);
		vector<vector<int>> adj(n+1);
		for(auto[a,b]:E)adj[a].push_back(b);
		while(!st.empty()){int u=st.back();st.pop_back();removed++;
			for(int v:adj[u])if(--indeg[v]==0)st.push_back(v);}
		assert(res==(removed==n));
		assert(cnt==removed);
		if(dag)assert(res);
		vector<int> pos(n+1,-1);
		for(int i=1;i<=cnt;i++){assert(pos[ord[i]]==-1);pos[ord[i]]=i;}
		for(auto[a,b]:E)if(pos[b]!=-1)assert(pos[a]!=-1&&pos[a]<pos[b]);
		checks++;
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
