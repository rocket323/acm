#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

struct node {
    int l, r;
} nd[maxl];

int n, m;
int f[10000010];
int st[maxl], top;

bool cmp(const node &a, const node &b) {
    return a.r < b.r;
}

void add(int p, int val) {
    if (top > 0 && f[st[top - 1]] >= val)
        return;
    st[top++] = p;
}

int query(int p) {
    int l = 0, r = top - 1, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (st[mid] <= p) {
            ans = st[mid];
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return f[ans];
}

void out() {
    printf("st: ");
    for (int i = 0; i < top; ++i)
        printf("%d ", f[st[i]]);
    puts("");
}

int main() {

    scanf("%d%d", &n, &m);
    top = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &nd[i].l, &nd[i].r);
    }
    sort(nd, nd + n, cmp);

    memset(f, 0, sizeof f);
    int ans = m;
    add(0, 0);
    for (int i = 0; i < n; ++i) {
        // out();
        int tmp = query(nd[i].l);
        int r = nd[i].r;
        f[r] = max(f[r], tmp + nd[i].r - nd[i].l);
        add(r, f[r]);
        // printf("f %d (%d, %d) %d\n", i, nd[i].l, nd[i].r, f[r]);

        ans = min(ans, m - f[r]);
    }
    printf("%d\n", ans);

    return 0;
}

