#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const int maxl = 7 * 1e5;
const int maxe = 5 * 1e6;
const int inf = 0x1f3f3f3f;

int n, m, a[maxl], b[maxl], p, tot, c;
char op[20];

class Splay {
public:
    struct Node {
        int ch[2];
        int size, fa;
        bool rev, same;
        int val;
        int sum, lsum, rsum;
        int max_sum;
    } t[maxe];

    int mset_;
    int root_;

    Splay() : mset_(0), root_(0) {
        memset(&t[0], 0, sizeof(Node));
        t[0].val = t[0].lsum = t[0].rsum = t[0].max_sum = -inf;
        int nd = newNode(0, 0, -inf);
        nd = newNode(nd, 1, -inf);
        splay(nd, 0);
    }

    int newNode(int fa, int d, int val) {
        int nd = ++mset_;
        if (fa) {
            t[fa].ch[d] = nd;
        }
        t[nd].ch[0] = t[nd].ch[1] = 0;
        t[nd].size = 1;
        t[nd].fa = fa;
        t[nd].rev = t[nd].same = false;
        t[nd].val = t[nd].sum = t[nd].lsum = t[nd].rsum = t[nd].max_sum = val;
        return nd;
    }

    int get(int x) {
        return t[t[x].fa].ch[1] == x;
    }

    void up(int x) {
        Node *p = &t[x], *lc = &t[t[x].ch[0]], *rc = &t[t[x].ch[1]];
        p->size = lc->size + rc->size + 1;
        p->sum = lc->sum + rc->sum + p->val;

        p->lsum = lc->lsum;
        p->lsum = max(p->lsum, lc->sum + p->val);
        p->lsum = max(p->lsum, lc->sum + p->val + rc->lsum);

        p->rsum = rc->rsum;
        p->rsum = max(p->rsum, rc->sum + p->val);
        p->rsum = max(p->rsum, rc->sum + p->val + lc->rsum);

        p->max_sum = p->val;
        p->max_sum = max(p->max_sum, lc->max_sum);
        p->max_sum = max(p->max_sum, rc->max_sum);
        p->max_sum = max(p->max_sum, lc->rsum + p->val);
        p->max_sum = max(p->max_sum, rc->lsum + p->val);
        p->max_sum = max(p->max_sum, lc->rsum + p->val + rc->lsum);
    }

    void down(int x) {
        if (x == 0)
            return;

        Node *p = &t[x], *lc = &t[t[x].ch[0]], *rc = &t[t[x].ch[1]];
        if (p->rev) {
            p->rev = false;
            lc->rev ^= 1;
            rc->rev ^= 1;
            swap(p->ch[0], p->ch[1]);
            swap(p->lsum, p->rsum);
        }

        if (p->same) {
            p->same = false;
            lc->same = rc->same = true;
            lc->val = rc->val = p->val;
            p->sum = p->lsum = p->rsum = p->max_sum = p->val * p->size;
            if (p->val < 0) {
                p->lsum = p->rsum = p->max_sum = p->val;
            }
        }
    }

    void attach(int x, int fa, int d) {
        t[fa].ch[d] = x;
        t[x].fa = fa;
    }

    void rotate(int x) {
        int fa = t[x].fa, gfa = t[fa].fa;
        int d1 = get(x), d2 = get(fa);
        down(t[x].ch[0]);
        down(t[x].ch[1]);
        down(t[fa].ch[d1 ^ 1]);
        attach(t[x].ch[d1 ^ 1], fa, d1);
        attach(x, gfa, d2);
        attach(fa, x, d1 ^ 1);
        up(fa);
        up(x);
    }

    void splay(int x, int goal) {
        down(x);
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

    int select(int k, int fa) {
        int nd = root_;
        while (true) {
            down(nd);
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

    void insert(int p, int a[], int n) {
        int head = 0, tail = 0;
        head = tail = newNode(0, 1, a[0]);
        for (int i = 1; i < n; i++) {
            tail = newNode(tail, 1, a[i]);
        }

        int l = select(p + 1, 0);
        int r = select(p + 2, l);
        t[r].ch[0] = head;
        t[head].fa = r;
        splay(tail, 0);
    }

    void del(int p, int n) {
        int l = select(p, 0);
        int r = select(p + n + 1, l);
        t[r].ch[0] = 0;
        splay(r, 0);
    }

    void modify(int p, int n, int c) {
        int l = select(p, 0);
        int r = select(p + n + 1, l);
        t[t[r].ch[0]].same = true;
        t[t[r].ch[0]].val = c;
        splay(t[r].ch[0], 0);
    }

    void reverse(int p, int n) {
        int l = select(p, 0);
        int r = select(p + n + 1, l);
        t[t[r].ch[0]].rev ^= 1;
        splay(t[r].ch[0], 0);
    }

    int sum(int p, int n) {
        int l = select(p, 0);
        int r = select(p + n + 1, l);
        down(t[r].ch[0]);
        return t[t[r].ch[0]].sum;
    }

    int maxSum() {
        down(root_);
        return t[root_].max_sum;
    }
} s;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    s.insert(0, a, n);

    for (int j = 1; j <= m; j++) {
        scanf("%s", op);
        if (strcmp(op, "INSERT") == 0) {
            scanf("%d%d", &p, &tot);
            for (int i = 0; i < tot; i++) {
                scanf("%d", &b[i]);
            }
            s.insert(p, b, tot);
        } else if (strcmp(op, "DELETE") == 0) {
            scanf("%d%d", &p, &tot);
            s.del(p, tot);
        } else if (strcmp(op, "MAKE-SAME") == 0) {
            scanf("%d%d%d", &p, &tot, &c);
            s.modify(p, tot, c);
        } else if (strcmp(op, "REVERSE") == 0) {
            scanf("%d%d", &p, &tot);
            s.reverse(p, tot);
        } else if (strcmp(op, "GET-SUM") == 0) {
            scanf("%d%d", &p, &tot);
            printf("%d\n", s.sum(p, tot));
        } else if (strcmp(op, "MAX-SUM") == 0) {
            printf("%d\n", s.maxSum());
        }
    }

    return 0;
}
