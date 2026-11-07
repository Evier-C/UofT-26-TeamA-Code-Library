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
		FW.init(n);
		for(int i=0;i<m;i++){
			int u=R(1,n),v=R(1,n);ll w=neg?R(-3,10):R(0,10);
			E.push_back({u,v,w});
			FW.d[u][v]=min(FW.d[u][v],w);
		}
		FW.floyd(n);
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
				ll exp=dist[t]==inf?FW.INF:bad[t]?-FW.INF:dist[t];
				assert(FW.d[s][t]==exp);checks++;
			}
		}
	}
	// large: no negative cycle
	{
		int n=300;FW.init(n);
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j&&R(0,3)==0)
			FW.d[i][j]=min(FW.d[i][j],(ll)R(0,1000000));
		FW.floyd(n);
		for(int i=1;i<=n;i++)assert(FW.d[i][i]==0);
		for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)if(FW.d[i][k]<FW.INF)
			for(int j=1;j<=n;j++)if(FW.d[k][j]<FW.INF)assert(FW.d[i][j]<=FW.d[i][k]+FW.d[k][j]);
		checks++;
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
