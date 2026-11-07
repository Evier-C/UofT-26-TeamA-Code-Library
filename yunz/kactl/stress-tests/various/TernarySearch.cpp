#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/various/TernarySearch.h"

// 头文件里的例子: f(x) = -(x-3)^2, F(x) = -(x-1)^2
int main(){
	ll checks=0;
	for(int l=-60;l<=60;l++)for(int r=l;r<=60;r++){
		int best=l;
		for(int i=l;i<=r;i++)if(f(i)>f(best))best=i;
		assert(tern(l,r)==best);checks++;
	}
	assert(tern(-1000000000,1000000000)==3);
	assert(tern(5,1000000000)==5&&tern(-1000000000,-7)==-7);
	assert(fabs(ternR(-100,100)-1)<1e-6);
	assert(fabs(ternR(3,10)-3)<1e-6);
	assert(fabs(ternR(-50,0.5)-0.5)<1e-6);
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
