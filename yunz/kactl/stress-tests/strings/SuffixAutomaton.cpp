#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/strings/SuffixAutomaton.h"

int main() {
	rep(it,0,20000) {
		int n = randIncl(11), A = randIncl(1, 3);
		string s;
		rep(i,0,n) s += char('a' + randRange(A));
		SAM sa;
		for (char c : s) sa.extend(c);
		set<string> subs;
		rep(i,0,n) rep(l,1,n-i+1) subs.insert(s.substr(i, l));
		// number of distinct substrings and the 2n-1 state bound
		ll cnt = 0;
		rep(v,1,sz(sa.q)) cnt += sa.q[v].len - sa.q[sa.q[v].link].len;
		assert(cnt == sz(subs));
		assert(sz(sa.q) <= max(n + 1, 2 * n - 1));
		// every string of length <= n+1 is accepted iff it is a substring,
		// and lands in a state with link.len < |t| <= len
		function<void(int, string&)> dfs = [&](int v, string& t) {
			if (!t.empty()) {
				bool in = subs.count(t);
				assert(in == (v >= 0));
				if (v < 0) return;
				assert(sa.q[sa.q[v].link].len < sz(t) && sz(t) <= sa.q[v].len);
			}
			if (sz(t) > n) return;
			rep(c,0,A+1) {
				char ch = char('a' + c);
				int w = sa.q[v].next.count(ch) ? sa.q[v].next[ch] : -1;
				t += ch;
				dfs(w, t);
				t.pop_back();
			}
		};
		string t;
		dfs(0, t);
		// suffixes end in the terminal states (link chain from last)
		set<int> term;
		for (int v = sa.last; v != -1; v = sa.q[v].link) term.insert(v);
		rep(i,0,n+1) {
			int v = 0;
			rep(j,i,n) v = sa.q[v].next[s[j]];
			assert(term.count(v));
		}
	}
	cout<<"Tests passed!"<<endl;
}
