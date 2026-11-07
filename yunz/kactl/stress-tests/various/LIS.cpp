#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/various/LIS.h"

int main(){
	mt19937_64 rng(14);
	ll checks=0;
	for(int it=0;it<20000;it++){ // 多组数据, 不清空
		int n=rng()%(it<10000?12:300),V=rng()%(n+5)+1;
		for(int i=1;i<=n;i++)a[i]=(int)(rng()%V)-V/2;
		vector<int>dp(n+1,0);int best=0;
		for(int i=1;i<=n;i++){
			dp[i]=1;
			for(int j=1;j<i;j++)if(a[j]<a[i])dp[i]=max(dp[i],dp[j]+1);
			best=max(best,dp[i]);
		}
		vector<int>id=lis(n);
		assert((int)id.size()==best);
		for(int i=0;i<(int)id.size();i++){
			assert(id[i]>=1&&id[i]<=n);
			if(i)assert(id[i-1]<id[i]&&a[id[i-1]]<a[id[i]]);
		}
		checks++;
	}
	int n=200000; // 大数据: 严格上升
	for(int i=1;i<=n;i++)a[i]=i*2;
	assert((int)lis(n).size()==n);
	for(int i=1;i<=n;i++)a[i]=n-i;
	assert((int)lis(n).size()==1);
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
