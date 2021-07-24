#include <bits/stdc++.h>
using namespace std;
const int maxl = 5e5 + 10;
const int inf = 0x3f3f3f3f;

int n, m, a[maxl], pos[maxl];
char s[100];

class Splay {
public:
    struct Node {
        int ch[2];
        int val, fa, size;
    } t[maxl];
    int mset_, root_;

    Splay() : mset_(0), root_(1) {
        memset(&t[0], 0, sizeof(Node));
        int l = newNode(0, 0, -inf);
        int r = newNode(l, 1, -inf);
        up(l);
    }

    int newNode(int fa, int d, int val) {
        int nd = ++mset_;
        if (fa) {
            t[fa].ch[d] = nd;
        }
        t[nd].ch[0] = t[nd].ch[1] = 0;
        t[nd].size = 1;
        t[nd].val = val;
        t[nd].fa = fa;
        return nd;
    }

    int get(int x) {
        return t[t[x].fa].ch[1] == x;
    }

    void attach(int x, int fa, int d) {
        t[fa].ch[d] = x;
        if (x) {
            t[x].fa = fa;
        }
        up(fa);
    }

    void up(int x) {
        if (x == 0)
            return;
        Node *p = &t[x], *lc = &t[t[x].ch[0]], *rc = &t[t[x].ch[1]];
        p->size = lc->size + rc->size + 1;
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
        while (x && t[x].fa != goal) {
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

    int select(int k, int fa) {
        int nd = root_;
        while (nd) {
            int son = t[nd].ch[0];
            if (k <= t[son].size) {
                nd = son;
            } else if (k > t[son].size + 1) {
                k -= t[son].size + 1;
                nd = t[nd].ch[1];
            } else {
                break;
            }
        }
        splay(nd, fa);
        return nd;
    }

    int pre(int nd) {
        nd = t[nd].ch[0];
        while (nd && t[nd].ch[1])
            nd = t[nd].ch[1];
        return nd;
    }

    int succ(int nd) {
        nd = t[nd].ch[1];
        while (nd && t[nd].ch[0])
            nd = t[nd].ch[0];
        return nd;
    }

    int del(int nd) {
        splay(nd, 0);
        int l = pre(nd), r = succ(nd);
        splay(l, 0);
        splay(r, l);
        t[r].ch[0] = 0;
        up(r);
        up(l);
    }

    void insert(int x, int y) {
        int l = select(x, 0);
        int r = select(x + 1, l);
        int t = newNode(r, 0, y);
        pos[y] = t;
        up(r);
        up(l);
        splay(t, 0);
    }

    void top(int x) {
        int nd = pos[x];
        del(nd);
        insert(1, x);
    }

    void bottom(int x) {
        int nd = pos[x];
        del(nd);
        insert(n, x);
    }

    void insert2(int x, int y) {
        int nd = pos[x];
        int p = ask(x) + 1;
        del(nd);
        insert(p + y, x);
    }

    void build(int a[], int n) {
        int head = 0, tail = 0;
        head = tail = newNode(0, 1, a[1]);
        pos[a[1]] = tail;
        for (int i = 2; i <= n; i++) {
            tail = newNode(tail, 1, a[i]);
            pos[a[i]] = tail;
        }
        attach(head, 2, 0);
        splay(tail, 0);
    }

    int ask(int x) {
        int nd = pos[x];
        splay(nd, 0);
        nd = t[nd].ch[0];
        return t[nd].size - 1;
    }

    int query(int x) {
        int nd = select(x + 1, 0);
        return t[nd].val;
    }

    void _out(int x) {
        if (x == 0)
            return;
        _out(t[x].ch[0]);
        printf("%d ", t[x].val);
        _out(t[x].ch[1]);
    }

    void out() {
        printf("x ");
        _out(root_);
        puts("");
    }
} sp;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    sp.build(a, n);
    // sp.out();

    for (int i = 0; i < m; ++i) {
        int x = 0, y = 0;
        scanf("%s", s);
        if (strcmp(s, "Top") == 0) {
            scanf("%d", &x);
            sp.top(x);
        } else if (strcmp(s, "Bottom") == 0) {
            scanf("%d", &x);
            sp.bottom(x);
        } else if (strcmp(s, "Insert") == 0) {
            scanf("%d%d", &x, &y);
            sp.insert2(x, y);
        } else if (strcmp(s, "Ask") == 0) {
            scanf("%d", &x);
            printf("%d\n", sp.ask(x));
        } else if (strcmp(s, "Query") == 0) {
            scanf("%d", &x);
            printf("%d\n", sp.query(x));
        }
        // printf("%s %d %d\n", s, x, y);
        // sp.out();
    }

    return 0;
}
