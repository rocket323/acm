#include <bits/stdc++.h>

const int maxl = 1e5 + 10;

struct node {
    int l, r;
    char col;
    char flag;
} nd[maxl * 8];

int t;
int n, m;
char s[maxl], ch[10];
int op, l, r;

char calc(int a, int b) {
    if (a == 'r' && b == 'y')
        return 'o';
    if (a == 'y' && b == 'r')
        return 'o';

    if (a == 'r' && b == 'b')
        return 'p';
    if (a == 'b' && b == 'r')
        return 'p';

    if (a == 'y' && b == 'b')
        return 'g';
    if (a == 'b' && b == 'y')
        return 'g';

    if (a == 'o' && b == 'b')
        return 'x';
    if (a == 'b' && b == 'o')
        return 'x';
    if (a == 'p' && b == 'y')
        return 'x';
    if (a == 'y' && b == 'p')
        return 'x';
    if (a == 'g' && b == 'r')
        return 'x';
    if (a == 'r' && b == 'g')
        return 'x';

    return b;
}

void build(int now, int l, int r) {
    nd[now].l = l;
    nd[now].r = r;
    nd[now].flag = 0;
    if (l < r) {
        int mid = (l + r) >> 1;
        build(now * 2, l, mid);
        build(now * 2 + 1, mid + 1, r);
        nd[now].col = calc(nd[now * 2].col, nd[now * 2 + 1].col);
    } else {
        nd[now].col = s[l];
    }
}

void pushDown(int now) {
    if (nd[now].flag == 0)
        return;

    if (nd[now].l < nd[now].r) {
        nd[now * 2].flag = nd[now * 2].col = nd[now].flag;
        nd[now * 2 + 1].flag = nd[now * 2 + 1].col = nd[now].flag;
    }
    nd[now].flag = 0;
}

void change(int now, int l, int r, char ch) {
    if (l <= nd[now].l && nd[now].r <= r) {
        nd[now].col = ch;
        nd[now].flag = ch;
        return;
    }

    pushDown(now);

    int mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid)
        change(now * 2, l, r, ch);
    if (r > mid)
        change(now * 2 + 1, l, r, ch);

    nd[now].col = calc(nd[now * 2].col, nd[now * 2 + 1].col);
}

int query(int now, int l, int r) {
    pushDown(now);
    if (l <= nd[now].l && nd[now].r <= r) {
        return nd[now].col;
    }

    int mid = (nd[now].l + nd[now].r) / 2;
    int lv = 0, rv = 0;
    if (l <= mid)
        lv = query(now * 2, l, r);
    if (r > mid)
        rv = query(now * 2 + 1, l, r);

    if (lv == 0)
        return rv;
    else if (rv == 0)
        return lv;
    return calc(lv, rv);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        scanf("%s", s + 1);

        build(1, 1, n);

        for (int i = 1; i <= m; i++) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d%s", &l, &r, ch);
                change(1, l, r, ch[0]);
            } else {
                scanf("%d%d", &l, &r);
                char ans = query(1, l, r);
                printf("%c\n", ans);
            }
        }
    }

    return 0;
}
