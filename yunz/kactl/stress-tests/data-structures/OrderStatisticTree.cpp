#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/OrderStatisticTree.h"

mt19937 rng(5);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

int main(){
	long long checks=0;
	ordered_set s;
	for(int it=0;it<300;it++){
		s.clear();
		set<int>b;
		int V=rnd(1,it<290?50:1000000000);
		for(int step=0;step<2000;step++){
			int c=rng()%4,x=rnd(-V,V);
			if(c==0)s.insert(x),b.insert(x);
			else if(c==1)s.erase(x),b.erase(x);
			else if(c==2){
				int r=(int)distance(b.begin(),b.lower_bound(x));
				if(b.size()<200||step%50==0){
					assert((int)s.order_of_key(x)==r);checks++;
				}
			}else{
				int k=rnd(0,(int)b.size());
				auto it2=s.find_by_order(k);
				if(k==(int)b.size())assert(it2==s.end());
				else if(b.size()<200||step%50==0){
					assert(*it2==*next(b.begin(),k));checks++;
				}
			}
			assert(s.size()==b.size());
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
