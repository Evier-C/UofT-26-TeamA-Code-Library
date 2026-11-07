#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/strings/MinRotation.h"

mt19937 rng(4);
char s[1000005];
ll checks=0;
void test(int n,int al){
	for(int i=1;i<=n;i++)s[i]='a'+rng()%al;
	s[n+1]=0;
	string str(s+1,s+n+1);
	int bk=1;string best=str;
	for(int k=2;k<=n;k++){
		string r=str.substr(k-1)+str.substr(0,k-1);
		if(r<best)best=r,bk=k;
	}
	assert(minrot(s,n)==bk);checks++;
}
int main(){
	for(int it=0;it<500000;it++)test(1+rng()%12,1+rng()%3);
	for(int it=0;it<50;it++)test(500+rng()%1000,1+rng()%2);
	// 周期串
	for(int it=0;it<1000;it++){
		int per=1+rng()%5,n=per*(1+rng()%6);
		for(int i=1;i<=per;i++)s[i]='a'+rng()%2;
		for(int i=per+1;i<=n;i++)s[i]=s[i-per];
		string str(s+1,s+n+1);
		int bk=1;string best=str;
		for(int k=2;k<=n;k++){
			string r=str.substr(k-1)+str.substr(0,k-1);
			if(r<best)best=r,bk=k;
		}
		assert(minrot(s,n)==bk);checks++;
	}
	int n=1000000;
	for(int i=1;i<=n;i++)s[i]='a'+(rng()%100000==0);
	int k=minrot(s,n);
	assert(k>=1&&k<=n);
	cout<<checks<<" checks"<<endl;
	cout<<"Tests passed!"<<endl;
}
