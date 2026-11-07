#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/strings/SuffixArray.h"

mt19937 rng(5);
char s[N];
ll checks=0;
void test(int n,int al){
	for(int i=1;i<=n;i++)s[i]='a'+rng()%al;
	s[n+1]=0;
	getsa(s,n);getheight(s,n);
	vector<int> id(n);
	iota(id.begin(),id.end(),1);
	sort(id.begin(),id.end(),[&](int a,int b){
		return strcmp(s+a,s+b)<0;
	});
	for(int i=1;i<=n;i++){
		assert(sa[i]==id[i-1]);
		assert(rk[sa[i]]==i);
		int k=0;
		if(i>1)while(s[sa[i]+k]&&s[sa[i]+k]==s[sa[i-1]+k])k++;
		assert(height[i]==k);
		checks++;
	}
}
int main(){
	// 先大后小, 测多组数据残留
	for(int it=0;it<300000;it++){
		int n=it%3==0?1+rng()%30:1+rng()%8;
		test(n,1+rng()%3);
	}
	for(int it=0;it<30;it++)test(2000+rng()%3000,1+rng()%3);
	for(int it=0;it<1000;it++)test(1+rng()%10,1+rng()%2);
	for(int i=1;i<=1000000;i++)s[i]='a'+rng()%26;
	getsa(s,1000000);getheight(s,1000000);
	for(int i=1;i<=1000000;i++)s[i]='a';
	getsa(s,1000000);getheight(s,1000000);
	for(int i=1;i<=1000000;i++)assert(sa[i]==1000000-i+1&&height[i]==i-1);
	cout<<checks<<" checks"<<endl;
	cout<<"Tests passed!"<<endl;
}
