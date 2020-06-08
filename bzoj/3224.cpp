#include <stdio.h>
#include <cstring>

const int maxe = 3e5;
const int maxl = 1e5 + 10;
const int inf = 0x7fffffff;

class Splay {
public:
    Splay() : mset_(0), root_(0) {}

    int get(int x) {
        return t[t[x].fa].ch[1] == x;
    }

    void up(int x) {
        t[x].size = t[t[x].ch[0]].size + t[t[x].ch[1]].size + t[x].cnt;
    }

    void attach(int x, int fa, int d) {
        t[fa].ch[d] = x;
        t[x].fa = fa;
    }

    void rotate(int x) {
        int fa = t[x].fa, gfa = t[fa].fa;
        int d1 = get(x), d2 = get(fa);
        attach(t[x].ch[d1 ^ 1], fa, d1);
        attach(x, gfa, d2);
        attach(fa, x, d1 ^ 1);
        up(fa);
        up(x);
    }

    void splay(int x, int goal) {
        while (t[x].fa != goal) {
            int fa = t[x].fa, gfa = t[fa].fa;
            int d1 = get(x), d2 = get(fa);
            if (gfa != goal) {
                if (d1 == d2)
                    rotate(fa);
                else
                    rotate(x);
            }
            rotate(x);
        }
        if (goal == 0)
            root_ = x;
    }

    int find(int val) {
        int nd = root_;
        while (t[nd].val != val && t[nd].ch[t[nd].val < val])
            nd = t[nd].ch[t[nd].val < val];
        return nd;
    }

    void insert(int val) {
        int nd = root_, fa = 0;
        while (nd && t[nd].val != val) {
            fa = nd;
            nd = t[nd].ch[t[nd].val < val];
        }
        if (nd) {
            t[nd].cnt++;
        } else {
            nd = ++mset_;
            if (fa)
                t[fa].ch[t[fa].val < val] = nd;
            t[nd].size = t[nd].cnt = 1;
            t[nd].fa = fa;
            t[nd].val = val;
        }
        splay(nd, 0);
    }

    int pre(int val, int kind) {
        splay(find(val), 0);
        int nd = root_;
        if (t[nd].val < val && kind == 0)
            return nd;
        if (t[nd].val > val && kind == 1)
            return nd;
        nd = t[nd].ch[kind];
        while (t[nd].ch[kind ^ 1])
            nd = t[nd].ch[kind ^ 1];
        return nd;
    }

    int getPre(int val, int kind) {
        return t[pre(val, kind)].val;
    }

    void remove(int val) {
        int last = pre(val, 0), next = pre(val, 1);
        splay(last, 0);
        splay(next, last);
        if (t[t[next].ch[0]].cnt > 1) {
            t[t[next].ch[0]].cnt--;
            splay(t[next].ch[0], 0);
        } else {
            t[next].ch[0] = 0;
        }
    }

    int kth(int k) {
        int nd = root_;
        if (t[nd].size < k)
            return inf;
        while (true) {
            int son = t[nd].ch[0];
            if (k <= t[son].size) {
                nd = son;
            } else if (k > t[son].size + t[nd].cnt) {
                k -= t[son].size + t[nd].cnt;
                nd = t[nd].ch[1];
            } else {
                return t[nd].val;
            }
        }
    }

    int getRank(int val) {
        splay(find(val), 0);
        return t[t[root_].ch[0]].size;
    }

public:
    struct Node {
        int ch[2];
        int cnt, size, val, fa;
    } t[maxe];

    int mset_;
    int root_;
} s;

int main() {
    s.insert(-inf);
    s.insert(inf);

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1)
            s.insert(x);
        else if (op == 2)
            s.remove(x);
        else if (op == 3)
            printf("%d\n", s.getRank(x));
        else if (op == 4)
            printf("%d\n", s.kth(x + 1));
        else if (op == 5)
            printf("%d\n", s.getPre(x, 0));
        else if (op == 6)
            printf("%d\n", s.getPre(x, 1));
    }
    return 0;
}
