#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/strings/Zfunc.h"

mt19937 rng(2);
char s[Zfunc::N],t[Zfunc::N];
ll checks=0;
int lcp(char*a,int n,char*b,int m){
	int k=0;
	while(k<n&&k<m&&a[k]==b[k])k++;
	return k;
}
void test(int n,int m,int al){
	for(int i=1;i<=n;i++)s[i]='a'+rng()%al;
	for(int i=1;i<=m;i++)t[i]='a'+rng()%al;
	s[n+1]=t[m+1]=0;
	Z.getz(s,n);
	for(int i=1;i<=n;i++){
		assert(Z.z[i]==lcp(s+i,n-i+1,s+1,n));checks++;
	}
	Z.getz(t,m);Z.exkmp(s,n,t,m);
	for(int i=1;i<=n;i++){
		assert(Z.ext[i]==lcp(s+i,n-i+1,t+1,m));checks++;
	}
}
int main(){
	for(int it=0;it<200000;it++)
		test(1+rng()%15,1+rng()%10,1+rng()%3);
	for(int it=0;it<100;it++)
		test(1000+rng()%3000,1+rng()%3000,1+rng()%2);
	cout<<checks<<" checks"<<endl;
	cout<<"Tests passed!"<<endl;
}
