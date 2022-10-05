#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

struct node {
    int a, b;
    int idx;
} p[maxl];

int n, m, ans[maxl];

bool cmp(const node &a, const node &b) {
    if (a.a != b.a)
        return a.a > b.a;
    return a.b > b.b;
}

int main() {
    scanf("%d%d", &n, &m);
    int t = n * (n - 1) / 2;
    for (int i = 1; i <= n; i++) {
        p[i].idx = i;
    }
    for (int i = 0; i < t; i++) {
        int x, y, a, b;
        scanf("%d%d%d%d", &x, &y, &a, &b);
        if (a < b) {
            swap(x, y);
            swap(a, b);
        }
        p[x].a += 1;
        p[x].b += a;
        p[y].b += b;
    }
    // for (int i = 1; i <= n; i++) {
    //     printf("%d %d %d\n", p[i].a, p[i].b, p[i].idx);
    // }
    sort(p + 1, p + n + 1, cmp);
    // for (int i = 1; i <= n; i++) {
    //     printf("%d %d %d\n", p[i].a, p[i].b, p[i].idx);
    // }

    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j < i; j++) {
            if (p[j].a > p[i].a || p[j].b > p[i].b)
                cnt++;
        }
        if (cnt < m)
            ans[p[i].idx] = 1;
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return 0;
}