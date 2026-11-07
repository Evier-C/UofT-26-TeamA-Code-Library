#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/strings/SuffixArray.h"

mt19937 rng(5);
char s[SuffixArray::N],s2[105];
SuffixArray SA2; // 第二个实例
ll checks=0;
void test(int n,int al){
	for(int i=1;i<=n;i++)s[i]='a'+rng()%al;
	s[n+1]=0;
	SA.getsa(s,n);SA.getheight(s,n);
	vector<int> id(n);
	iota(id.begin(),id.end(),1);
	sort(id.begin(),id.end(),[&](int a,int b){
		return strcmp(s+a,s+b)<0;
	});
	for(int i=1;i<=n;i++){
		assert(SA.sa[i]==id[i-1]);
		assert(SA.rk[SA.sa[i]]==i);
		int k=0;
		if(i>1)while(s[SA.sa[i]+k]&&s[SA.sa[i]+k]==s[SA.sa[i-1]+k])k++;
		assert(SA.height[i]==k);
		checks++;
	}
}
int main(){
	// 两个实例互不影响
	for(int it=0;it<20000;it++){
		int n=1+rng()%20,n2=1+rng()%20;
		for(int i=1;i<=n;i++)s[i]='a'+rng()%2;
		for(int i=1;i<=n2;i++)s2[i]='a'+rng()%3;
		s[n+1]=s2[n2+1]=0;
		SA.getsa(s,n);
		SA2.getsa(s2,n2);
		SA2.getheight(s2,n2);
		SA.getheight(s,n);
		for(int i=2;i<=n;i++)assert(strcmp(s+SA.sa[i-1],s+SA.sa[i])<0);
		for(int i=2;i<=n2;i++){
			int a=SA2.sa[i-1],b=SA2.sa[i],k=0;
			assert(strcmp(s2+a,s2+b)<0);
			while(s2[a+k]&&s2[a+k]==s2[b+k])k++;
			assert(SA2.height[i]==k);
		}
		checks++;
	}
	// 先大后小, 测多组数据残留
	for(int it=0;it<300000;it++){
		int n=it%3==0?1+rng()%30:1+rng()%8;
		test(n,1+rng()%3);
	}
	for(int it=0;it<30;it++)test(2000+rng()%3000,1+rng()%3);
	for(int it=0;it<1000;it++)test(1+rng()%10,1+rng()%2);
	for(int i=1;i<=1000000;i++)s[i]='a'+rng()%26;
	SA.getsa(s,1000000);SA.getheight(s,1000000);
	for(int i=1;i<=1000000;i++)s[i]='a';
	SA.getsa(s,1000000);SA.getheight(s,1000000);
	for(int i=1;i<=1000000;i++)assert(SA.sa[i]==1000000-i+1&&SA.height[i]==i-1);
	cout<<checks<<" checks"<<endl;
	cout<<"Tests passed!"<<endl;
}
