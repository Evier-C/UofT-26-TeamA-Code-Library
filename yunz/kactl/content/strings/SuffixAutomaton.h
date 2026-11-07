/**
 * Author: cp-algorithms
 * Date: 2026-03-16
 * License: Unknown
 * Source: https://cp-algorithms.com/string/suffix-automaton.html
 * Description: 后缀自动机. 节点 0 总是起始节点, 但节点不一定按拓扑序排列.
 * 每个状态有 len (最长串长度), link (后缀链接), next (转移).
 * Usage: SAM sam; for (char c : s) sam.extend(c);
 * sam.q[v].len; sam.q[v].link; sam.q[v].next[c];
 * Time: O(n \log \Sigma)
 * Status: untested
 */
struct SAM {
    struct state {
        int len, link;
        map<char, int> next;
    };
    vector<state> q;
    int last;
    SAM() : last(0) { q.push_back({0,-1}); }
    int new_node() {
        q.emplace_back(); return sz(q) - 1;
    }
    void extend(char c) {
        int cur = new_node(), i = last;
        q[cur].len = q[last].len + 1;
        while (i != -1 && !q[i].next.contains(c))
            q[i].next[c] = cur, i = q[i].link;
        if (i == -1) q[cur].link = 0;
        else {
            int j = q[i].next[c];
            if (q[i].len+1 == q[j].len)
                q[cur].link = j;
            else {
                int clone = new_node();
                q[clone].len = q[i].len + 1;
                q[clone].next = q[j].next;
                q[clone].link = q[j].link;
                while (i != -1 && q[i].next[c] == j) {
                    q[i].next[c] = clone;
                    i = q[i].link;
                }
                q[j].link = q[cur].link = clone;
            }
        }
        last = cur;
    }
};