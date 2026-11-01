#include "../utilities/template.h"
#include "../utilities/random.h"

#define pb push_back
#include "../../content/various/ExpressionTree.h"

// Compare the fully parenthesized tree against a recursive-descent parser.
// Operators: + - * / (left-assoc), unary minus (shown as _), parentheses.
string show(Val* v) {
	if (!v->op) return to_string(v->v);
	if (v->op == '_') return "(_" + show(v->l) + ")";
	return "(" + show(v->l) + v->op + show(v->r) + ")";
}

string str; int pos;
string expr();
string primary() {
	if (str[pos] == '(') {
		pos++;
		string r = expr();
		assert(str[pos] == ')');
		pos++;
		return r;
	}
	int v = 0;
	while (pos < sz(str) && isdigit(str[pos])) v = v * 10 + str[pos++] - '0';
	return to_string(v);
}
string unary() {
	if (str[pos] == '-') { pos++; return "(_" + unary() + ")"; }
	return primary();
}
string term() {
	string l = unary();
	while (pos < sz(str) && (str[pos] == '*' || str[pos] == '/')) {
		char c = str[pos++];
		l = "(" + l + c + unary() + ")";
	}
	return l;
}
string expr() {
	string l = term();
	while (pos < sz(str) && (str[pos] == '+' || str[pos] == '-')) {
		char c = str[pos++];
		l = "(" + l + c + term() + ")";
	}
	return l;
}

string gen(int d) {
	int t = randRange(6);
	if (d <= 0 || t < 2) return to_string(randRange(randRange(3) ? 10 : 1000));
	if (t == 2) return "-" + gen(d - 1);
	if (t == 3) return "(" + gen(d - 1) + ")";
	return gen(d - 1) + "+-*/"[randRange(4)] + gen(d - 1);
}

int main() {
	rep(it,0,200000) {
		string s = gen(randRange(6));
		last = 0; // reset the node pool for each expression
		str = s, pos = 0;
		string expected = expr();
		assert(pos == sz(s));
		assert(show(parseExpression(s)) == expected);
	}
	cout<<"Tests passed!"<<endl;
}
