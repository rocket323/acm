#include <bits/stdc++.h>

const int maxl = 1e5 + 10;

struct node {
    int l, r;
    char col[8];
    char flag;
} nd[maxl * 4];

int t;
int n, m;
char s[maxl], ch[10];
int op, l, r;
char a[8] = {' ', 'r', 'y', 'b', 'o', 'p', 'g', 'x'};

int getIdx(char ch) {
    switch (ch) {
        case ' ':
            return 0;
        case 'r':
            return 1;
        case 'y':
            return 2;
        case 'b':
            return 3;
        case 'o':
            return 4;
        case 'p':
            return 5;
        case 'g':
            return 6;
        case 'x':
            return 7;
    }
    return 0;
}

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

void update(int now) {
    for (int i = 0; i < 8; i++) {
        int idx = getIdx(nd[now * 2].col[i]);
        nd[now].col[i] = nd[now * 2 + 1].col[idx];
    }
}

void build(int now, int l, int r) {
    nd[now].l = l;
    nd[now].r = r;
    nd[now].flag = 0;
    if (l < r) {
        int mid = (l + r) >> 1;
        build(now * 2, l, mid);
        build(now * 2 + 1, mid + 1, r);
        update(now);
    } else {
        for (int i = 0; i < 8; i++) {
            nd[now].col[i] = calc(a[i], s[l]);
        }
    }
}

void cover(int now, int ch) {
    nd[now].flag = ch;
    for (int i = 0; i < 8; i++) {
        int x = a[i];
        for (int j = nd[now].l; j <= nd[now].r; j++) {
            x = calc(x, ch);
            if (x == ch)
                break;
        }
        nd[now].col[i] = x;
    }
}

void pushDown(int now) {
    if (nd[now].flag == 0)
        return;

    if (nd[now].l < nd[now].r) {
        cover(now * 2, nd[now].flag);
        cover(now * 2 + 1, nd[now].flag);
    }
    nd[now].flag = 0;
}

void change(int now, int l, int r, char ch) {
    if (l <= nd[now].l && nd[now].r <= r) {
        cover(now, ch);
        return;
    }

    pushDown(now);

    int mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid)
        change(now * 2, l, r, ch);
    if (r > mid)
        change(now * 2 + 1, l, r, ch);

    update(now);
}

int query(int now, int l, int r, int i) {
    pushDown(now);
    if (l <= nd[now].l && nd[now].r <= r) {
        return nd[now].col[i];
    }

    int mid = (nd[now].l + nd[now].r) / 2;
    int ch = ' ';
    int idx = i;
    if (l <= mid) {
        ch = query(now * 2, l, r, idx);
        idx = getIdx(ch);
    }

    if (r > mid) {
        ch = query(now * 2 + 1, l, r, idx);
    }

    return ch;
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
                char ans = query(1, l, r, 0);
                printf("%c\n", ans);
            }
        }
    }

    return 0;
}
