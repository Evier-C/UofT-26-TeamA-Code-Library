#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/strings/Manacher.h"

mt19937 rng(3);
char s[N];
ll checks=0;
bool pal(int l,int r){
	while(l<r)if(s[l++]!=s[r--])return 0;
	return 1;
}
void test(int n,int al){
	for(int i=1;i<=n;i++)s[i]='a'+rng()%al;
	s[n+1]=0;
	int len=manacher(s,n),best=0;
	for(int l=1;l<=n;l++)for(int r=l;r<=n;r++)
		if(pal(l,r))best=max(best,r-l+1);
	assert(len==best);checks++;
	// 每个中心
	for(int i=1;i<=n;i++){
		int k=0;
		while(i-k-1>=1&&i+k+1<=n&&s[i-k-1]==s[i+k+1])k++;
		assert(p[2*i]-1==2*k+1);checks++;
		int K=2*i-p[2*i]; // (k-p[k])/2+1
		assert(K/2+1==i-k);
	}
	for(int i=0;i<=n;i++){
		int k=0;
		while(i-k>=1&&i+1+k<=n&&s[i-k]==s[i+1+k])k++;
		assert(p[2*i+1]-1==2*k);checks++;
		assert((2*i+1-p[2*i+1])/2+1==i-k+1);
	}
}
int main(){
	for(int it=0;it<100000;it++)test(rng()%16,1+rng()%3);
	for(int it=0;it<20;it++)test(300+rng()%200,1+rng()%2);
	cout<<checks<<" checks"<<endl;
	cout<<"Tests passed!"<<endl;
}
