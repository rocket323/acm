#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

struct node {
    int r, c, a, idx;
} p[maxl];

int n, m, k, rmax[maxl], cmax[maxl];
int f[maxl], rk[maxl];

bool cmp(const node &a, const node &b) {
    return a.a > b.a;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i <= n; i++)
        rmax[i] = -1;
    for (int i = 0; i <= m; i++)
        cmax[i] = -1;
    for (int i = 0; i < k; i++) {
        scanf("%d%d%d", &p[i].r, &p[i].c, &p[i].a);
        p[i].idx = i;
    }
    sort(p, p + k, cmp);

    int j = -1;
    for (int i = 0; i < k; i++) {
        while (j + 1 < i && p[j + 1].a > p[i].a) {
            rmax[p[j + 1].r] = max(rmax[p[j + 1].r], f[p[j + 1].idx]);
            cmax[p[j + 1].c] = max(cmax[p[j + 1].c], f[p[j + 1].idx]);
            j++;
        }

        f[p[i].idx] = max(f[p[i].idx], rmax[p[i].r] + 1);
        f[p[i].idx] = max(f[p[i].idx], cmax[p[i].c] + 1);
    }

    for (int i = 0; i < k; i++) {
        printf("%d\n", f[i]);
    }

    return 0;
}
