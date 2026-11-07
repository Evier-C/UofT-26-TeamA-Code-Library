// Checks the slope trick example in data-structures/chapter.tex (not a header):
// min sum |a_i - b_i| over non-decreasing b, and the strictly increasing variant.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rng(23);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

ll slope(int n,vector<ll>a){ // copied from the guide
	priority_queue<ll> L; // 大根堆, 存左边的拐点
	ll ans=0;
	for(int i=1;i<=n;i++){
		L.push(a[i]);
		if(L.top()>a[i]){ // 最小值增加 top - a[i]
			ans+=L.top()-a[i];
			L.pop();
			L.push(a[i]);
		}
	}
	return ans;
}
// brute DP: optimal b can be taken from the values of a
ll brute(int n,const vector<ll>&a){
	vector<ll>v(a.begin()+1,a.end());
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	int k=v.size();
	vector<ll>dp(k,0);
	for(int i=1;i<=n;i++){
		ll best=LLONG_MAX;
		for(int j=0;j<k;j++){
			best=min(best,dp[j]);
			dp[j]=best+llabs(a[i]-v[j]);
		}
	}
	return *min_element(dp.begin(),dp.end());
}
// brute for strictly increasing integer b: search b_i in a small range
ll bruteStrict(int n,const vector<ll>&a){
	int lo=-50,hi=100;
	vector<ll>dp(hi-lo+1,0);
	for(int i=1;i<=n;i++){
		vector<ll>nd(hi-lo+1,LLONG_MAX/4);
		ll best=LLONG_MAX/4;
		for(int x=lo;x<=hi;x++){
			nd[x-lo]=(i==1?0:best)+llabs(a[i]-x);
			best=min(best,dp[x-lo]);
		}
		dp=nd;
	}
	return *min_element(dp.begin(),dp.end());
}

int main(){
	long long checks=0;
	for(int it=0;it<20000;it++){
		int n=rnd(1,12),V=rnd(1,it%2?10:1000);
		vector<ll>a(n+1);
		for(int i=1;i<=n;i++)a[i]=rnd(-V,V);
		assert(slope(n,a)==brute(n,a));
		checks++;
		if(V<=10){
			vector<ll>c=a;
			for(int i=1;i<=n;i++)c[i]-=i;
			assert(slope(n,c)==bruteStrict(n,a));
			checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
