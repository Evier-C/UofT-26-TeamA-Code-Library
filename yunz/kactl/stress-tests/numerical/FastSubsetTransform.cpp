#include "../utilities/template.h"

#include "../../content/numerical/FastSubsetTransform.h"

// Tests the active (XOR) variant: convolution and point_add / point_eval.
int main() {
	rep(k,0,10) rep(it,0,20) {
		int n = 1 << k;
		vl a(n), b(n), target(n);
		for(auto &x: a) x = rand() % 6 - 2;
		for(auto &x: b) x = rand() % 6 - 2;
		rep(i,0,n) rep(j,0,n) target[i ^ j] += a[i] * b[j];
		assert(conv(a, b) == target);

		vl t = a;
		FST(t, false);
		rep(q,0,10) {
			int i = rand() % n;
			ll val = rand() % 11 - 5;
			point_add(t, i, val);
			a[i] += val;
			rep(j,0,n) assert(point_eval(t, j) == a[j]);
		}
		FST(t, true);
		assert(t == a);
	}
	cout<<"Tests passed!"<<endl;
}
