#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

using ll = long long;
const int maxl = 2e5 + 10;
int n, m, k;
int c[maxl], d[maxl];

struct node {
    int a, b, c, w;
    int ans;
} e[maxl], q[maxl];

bool cmp1(const node &n1, const node &n2) {
    if (n1.a != n2.a) return n1.a < n2.a;
    if (n1.b != n2.b) return n1.b < n2.b;
    return n1.c < n2.c;
}

bool cmp2(const node &n1, const node &n2) {
    if (n1.b != n2.b) return n1.b < n2.b;
    return n1.c < n2.c;
}

int lowbit(int n) {
    return n & -n;
}

void add(int n, int val) {
    n += 2;
    while (n < maxl) {
        c[n] += val;
        n += lowbit(n);
    }
}

int sum(int n) {
    n += 2;
    int ans = 0;
    while (n) {
        ans += c[n];
        n -= lowbit(n);
    }
    return ans;
}

void dfs(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    dfs(l, mid);
    dfs(mid + 1, r);

    sort(e + l, e + mid + 1, cmp2);
    sort(e + mid + 1, e + r + 1, cmp2);

    int p = l;
    for (int i = mid + 1; i <= r; i++) {
        while (p <= mid && e[p].b <= e[i].b) {
            add(e[p].c, e[p].w);
            p++;
        }
        e[i].ans += sum(e[i].c);
    }
    for (int i = l; i < p; i++)
        add(e[i].c, -e[i].w);
}

int main() {
    scanf("%d%d", &n, &k);
    m = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &q[i].a, &q[i].b, &q[i].c);
    }
    sort(q + 1, q + n + 1, cmp1);
    for (int i = 1; i <= n; i++) {
        if (m == 0 || !(q[i].a == e[m].a && q[i].b == e[m].b && q[i].c == e[m].c)) {
            ++m;
            e[m] = q[i];
            e[m].w = 1;
        } else if (m > 0) {
            e[m].w++;
        }
    }
    int nn = n;
    n = m;
    dfs(1, n);
    for (int i = 1; i <= n; i++) {
        e[i].ans += e[i].w - 1;
    }
    for (int i = 1; i <= n; i++) {
        d[e[i].ans] += e[i].w;
    }
    for (int i = 0; i < nn; i++) {
        printf("%d\n", d[i]);
    }
    return 0;
}
