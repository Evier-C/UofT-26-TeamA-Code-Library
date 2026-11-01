#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/geometry/HalfPlane.h"

// Compare the area of halfPlaneIntersection with clipping a bounding box
// by each half-plane (Sutherland-Hodgman) in long double.
typedef long double LD;
struct Q { LD x, y; };

vector<Q> clip(const vector<Q>& poly, const Line& L) {
	LD ax = L[0].x, ay = L[0].y, dx = L[1].x - ax, dy = L[1].y - ay;
	auto side = [&](Q p) { return dx * (p.y - ay) - dy * (p.x - ax); };
	vector<Q> out;
	int n = sz(poly);
	rep(i,0,n) {
		Q p = poly[i], q = poly[(i + 1) % n];
		LD fp = side(p), fq = side(q);
		if (fp >= 0) out.push_back(p);
		if ((fp > 0 && fq < 0) || (fp < 0 && fq > 0)) {
			LD t = fp / (fp - fq);
			out.push_back({p.x + (q.x - p.x) * t, p.y + (q.y - p.y) * t});
		}
	}
	return out;
}

template<class V> LD area(const V& v) {
	if (sz(v) < 3) return 0;
	LD a = 0;
	rep(i,0,sz(v)) {
		int j = (i + 1) % sz(v);
		a += (LD)v[i].x * v[j].y - (LD)v[j].x * v[i].y;
	}
	return a / 2;
}

void test(int R, int maxLines, int iters) {
	const int B = 10;
	vector<P> box = {P(-B, -B), P(B, -B), P(B, B), P(-B, B)};
	rep(it,0,iters) {
		vector<Line> vs;
		rep(i,0,4) vs.push_back({box[i], box[(i + 1) % 4]});
		int k = randIncl(maxLines);
		rep(i,0,k) {
			P a(randIncl(-R, R), randIncl(-R, R)), b(randIncl(-R, R), randIncl(-R, R));
			if (a == b) continue;
			vs.push_back({a, b});
			if (randRange(4) == 0) vs.push_back({a, b}); // duplicate
			if (randRange(4) == 0) vs.push_back({b, a}); // opposite direction
		}
		shuffle_vec(vs);
		vector<Q> poly;
		for (P p : box) poly.push_back({(LD)p.x, (LD)p.y});
		for (auto& L : vs) poly = clip(poly, L);
		auto res = halfPlaneIntersection(vs);
		assert(fabsl(area(poly) - area(res)) < 1e-6);
	}
}

int main() {
	test(2, 6, 100000);
	test(5, 6, 100000);
	test(15, 20, 30000);
	test(100, 20, 30000);
	cout<<"Tests passed!"<<endl;
}
