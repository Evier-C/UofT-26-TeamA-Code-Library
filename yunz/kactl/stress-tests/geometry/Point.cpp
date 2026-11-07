#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/geometry/Point.h"

typedef long double ld;
typedef complex<ld> C;
mt19937 rng(1);
int rd(int lo,int hi){return lo+(int)(rng()%(hi-lo+1));}
bool near(ld a,ld b){return fabsl(a-b)<1e-9*max((ld)1,fabsl(b));}

int main(){
	ll checks=0;
	for(int it=0;it<300000;it++){
		int L=it%2?5:1000;
		Point a(rd(-L,L),rd(-L,L)),b(rd(-L,L),rd(-L,L)),c(rd(-L,L),rd(-L,L));
		C A(a.x,a.y),B(b.x,b.y),Cc(c.x,c.y);
		T k=rd(-5,5);
		Point s=a+b,d=a-b,m=a*k;
		assert(s.x==a.x+b.x&&s.y==a.y+b.y);
		assert(d.x==a.x-b.x&&d.y==a.y-b.y);
		assert(m.x==a.x*k&&m.y==a.y*k);
		if(k!=0){
			Point q=a/k;
			assert(near(q.x,(ld)a.x/k)&&near(q.y,(ld)a.y/k));
		}
		assert(near(a.dot(b),real(conj(A)*B)));
		assert(near(a.cross(b),imag(conj(A)*B)));
		assert(near(a.cross(b,c),imag(conj(B-A)*(Cc-A))));
		assert(near(a.len2(),norm(A)));
		assert(near(a.len(),abs(A)));
		Point p=a.perp();
		assert(near(p.x,real(A*C(0,1)))&&near(p.y,imag(A*C(0,1))));
		ld t=(ld)rd(-1000,1000)/100;
		Point r=a.rotate(t);C R=A*polar((ld)1,t);
		assert(fabsl(r.x-real(R))<1e-9&&fabsl(r.y-imag(R))<1e-9);
		// == and < agree with exact comparison on integer points
		assert((a==b)==(a.x==b.x&&a.y==b.y));
		assert((a<b)==(make_pair(a.x,a.y)<make_pair(b.x,b.y)));
		if(!(a==Point(0,0))){
			assert(near(a.angle(),arg(A)));
			Point u=a.unit();
			assert(near(u.len(),1)&&fabs(u.cross(a))<1e-9&&u.dot(a)>0);
		}
		checks+=14;
	}
	// eps behaviour
	assert(sgn(1e-12)==0&&sgn(-1e-12)==0&&sgn(1e-6)==1&&sgn(-1e-6)==-1);
	assert(Point(1,2)==Point(1+1e-12,2-1e-12));
	assert(Point(1+1e-12,1)<Point(1,2)&&!(Point(1,2)<Point(1+1e-12,2)));
	checks+=3;
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
