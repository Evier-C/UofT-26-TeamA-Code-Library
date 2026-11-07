#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/FloydWarshall.h"

mt19937 rng(123);
int R(int a,int b){return rng()%(b-a+1)+a;}

int main(){
	int checks=0;
	for(int it=0;it<3000;it++){
		int n=R(1,8),m=R(0,20);
		bool neg=it%2;
		vector<array<ll,3>> E;
		init(n);
		for(int i=0;i<m;i++){
			int u=R(1,n),v=R(1,n);ll w=neg?R(-3,10):R(0,10);
			E.push_back({u,v,w});
			d[u][v]=min(d[u][v],w);
		}
		floyd(n);
		// brute: Bellman-Ford from each source, n*2 rounds then mark
		for(int s=1;s<=n;s++){
			const ll inf=LLONG_MAX;
			vector<ll> dist(n+1,inf);dist[s]=0;
			for(int r=0;r<n;r++)for(auto[u,v,w]:E)
				if(dist[u]!=inf&&dist[u]+w<dist[v])dist[v]=dist[u]+w;
			vector<int> bad(n+1);
			for(int r=0;r<=n;r++)for(auto[u,v,w]:E)
				if(dist[u]!=inf&&(bad[u]||dist[u]+w<dist[v]))
					bad[v]=1,dist[v]=min(dist[v],dist[u]+w);
			for(int t=1;t<=n;t++){
				ll exp=dist[t]==inf?INF:bad[t]?-INF:dist[t];
				assert(d[s][t]==exp);checks++;
			}
		}
	}
	// large: no negative cycle
	{
		int n=300;init(n);
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j&&R(0,3)==0)
			d[i][j]=min(d[i][j],(ll)R(0,1000000));
		floyd(n);
		for(int i=1;i<=n;i++)assert(d[i][i]==0);
		for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)if(d[i][k]<INF)
			for(int j=1;j<=n;j++)if(d[k][j]<INF)assert(d[i][j]<=d[i][k]+d[k][j]);
		checks++;
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
