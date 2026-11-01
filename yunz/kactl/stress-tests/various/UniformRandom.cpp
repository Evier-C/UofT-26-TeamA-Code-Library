#include "../utilities/template.h"

#include "../../content/various/UniformRandom.h"

int main() {
	const int K = 7, ITS = 700000;
	vi cnt(K);
	rep(i,0,ITS) {
		int x = urand(-3, 3);
		assert(-3 <= x && x <= 3);
		cnt[x + 3]++;
	}
	for (int c : cnt) assert(abs(c - ITS / K) < ITS / K / 20); // within 5%
	rep(i,0,1000) assert(urand(5, 5) == 5);
	bool neg = false, pos = false;
	rep(i,0,1000) {
		int x = urand(INT_MIN, INT_MAX);
		neg |= x < 0, pos |= x > 0;
	}
	assert(neg && pos);
	cout<<"Tests passed!"<<endl;
}
