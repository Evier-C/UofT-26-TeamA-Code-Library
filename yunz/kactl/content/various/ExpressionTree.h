/**
 * Author: Robert Chung
 * License: CC0
 * Source: CP-algorithms
 * Description: 为左结合运算构建表达式树。
 * 按需修改 N 与 prec()。
 * Usage: Val *root = parseExpression(s); // 之后在树上 dp...
 * Time: O(N)
 * Status: tested on https://dmoj.ca/problem/acsl1p6, https://dmoj.ca/problem/riddletroll
 */
#pragma once

const int N = 2e6; // 树的最大节点数 取 |S| 即可
struct Val { // 每个节点 32 字节
    int v; // 仅当 op = 0 时使用
    char op; Val *l, *r; // 仅当 op 非 0 时使用
    Val(int v=0) : v(v), op(0), l(0), r(0) {}
    Val(char op, Val *l, Val *r) : op(op), l(l), r(r) {}
};
Val arr[N]; int last = 0;

Val *parseExpression(string &s) {
    using C = array<int, 3>; // 优先级比较键
    vector<pair<C, char>> ops;
    vector<Val*> vals;
    int depth = 0;

    auto prec = [&](char c, int i) -> C { // 改成你的运算符
        int r;
        if (c == '+' || c == '-') r = 0;
        else if (c == '*' || c == '/' || c == '_') r = 1;
        else assert(0); // 右结合用 i, 左结合用 -i
        return {depth, r, c == '_' ? i : -i}; 
    };
    auto clear = [&](C minp) {
        while (!ops.empty()) {
            auto [p, c] = ops.back();
            if (p < minp) break;
            ops.pop_back();
            auto b = vals.back(); vals.pop_back();
            if (c == '_') {  // 一元运算
                vals.pb(&(arr[last++] = Val(c, b, 0)));
            } else { // 二元运算
                auto a = vals.back(); vals.pop_back();
                vals.pb(&(arr[last++] = Val(c, a, b)));
            }
        }
    };
    for (int i = -1; char c : s) { i++;
        bool pdigit = i >= 1 && '0' <= s[i-1] && s[i-1] <= '9';
        if (c == '(') depth++;
        else if (c == ')') depth--;
        else if ('0' <= c && c <= '9') {
            if (pdigit) vals.back()->v = 10*vals.back()->v + c-'0';
            else vals.pb(&(arr[last++] = Val(c-'0')));
        } else {
            // 一元运算
            if (c == '-' && !pdigit
                && !(i >= 1 && s[i-1] == ')')) c = '_';
            clear(prec(c, i)); ops.pb({prec(c, i), c});
        }
    }
    clear({-1});
    return vals[0];
}