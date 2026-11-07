#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/SCC.h"

mt19937 rng(3);
int R(int a,int b){return rng()%(b-a+1)+a;}

int main(){
	long long checks=0;
	for(int it=0;it<20000;it++){
		bool big=it>=19995;
		int n=big?R(1000,2000):R(1,9),m=big?R(0,3*n):R(0,20);
		init(n);
		vector<pair<int,int>> E;
		vector<vector<char>> r(n+1,vector<char>(n+1));
		for(int i=0;i<m;i++){int u=R(1,n),v=R(1,n);g[u].push_back(v);E.push_back({u,v});}
		for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
		shrink(n);
		// brute reachability
		for(int s=1;s<=n;s++){
			vector<int> st={s};r[s][s]=1;
			while(!st.empty()){int u=st.back();st.pop_back();
				for(int v:g[u])if(!r[s][v])r[s][v]=1,st.push_back(v);}
		}
		vector<int> cs(cnt+1);
		for(int u=1;u<=n;u++){assert(scc[u]>=1&&scc[u]<=cnt);cs[scc[u]]++;}
		for(int i=1;i<=cnt;i++)assert(cs[i]==sz[i]&&sz[i]>0);
		for(int u=1;u<=n;u++)for(int v=1;v<=n;v++){
			assert((scc[u]==scc[v])==(r[u][v]&&r[v][u]));checks++;
		}
		// reverse topological ids, DAG edges
		int ec=0;
		for(auto[u,v]:E)if(scc[u]!=scc[v])assert(scc[u]>scc[v]),ec++;
		int hc=0;
		for(int i=1;i<=cnt;i++)for(int j:h[i])assert(i>j),hc++;
		assert(hc==ec);
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
