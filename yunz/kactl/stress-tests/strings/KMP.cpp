#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/strings/KMP.h"

mt19937 rng(1);
char s[N],t[N];
ll checks=0;
void test(int n,int m,int al){
	for(int i=1;i<=n;i++)s[i]='a'+rng()%al;
	for(int i=1;i<=m;i++)t[i]='a'+rng()%al;
	s[n+1]=t[m+1]=0;
	vector<int> occ=kmp(s,n,t,m);
	// nxt 暴力
	if(m<=60)for(int i=1;i<=m;i++){
		int best=0;
		for(int L=1;L<i;L++)
			if(!memcmp(t+1,t+i-L+1,L))best=L;
		assert(nxt[i]==best);checks++;
	}
	vector<int> bf;
	for(int i=1;i+m-1<=n;i++)
		if(!memcmp(s+i,t+1,m))bf.push_back(i);
	assert(occ==bf);checks++;
}
int main(){
	for(int it=0;it<200000;it++){
		int al=1+rng()%3;
		test(rng()%15,1+rng()%6,al);
	}
	for(int it=0;it<200;it++)test(1000+rng()%5000,1+rng()%10,1+rng()%2);
	test(1000000,3,1);
	cout<<checks<<" checks"<<endl;
	cout<<"Tests passed!"<<endl;
}
