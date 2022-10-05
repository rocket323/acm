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
    int idx, t;
};

int t, n, m;
int a[maxl], b[maxl], d[maxl];
int ans[maxl];

bool cmp(const node &a, const node &b) {
    return a.t < b.t;
}

int gao(int b, int a, int d) {
    if (a == b)
        return 0;
    if ((b - a) / abs(b - a) != d)
        return -1;
    return abs(b - a);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &a[i], &d[i]);
        }
        for (int i = 1; i <= m; i++) {
            scanf("%d", &b[i]);
        }
        memset(ans, 0, sizeof(ans));
        for (int i = 1; i <= m; i++) {
            vector<node> v;
            for (int j = 1; j <= n; j++) {
                int x = gao(b[i], a[j], d[j]);
                if (x >= 0) {
                    // cout << b[i] << ' ' << j << ' ' << a[j] << ' ' << x << endl;
                    v.push_back(node{j, x});
                }
            }
            if (v.empty())
                continue;
            sort(v.begin(), v.end(), cmp);
            // printf("%d:\n", b[i]);
            for (int j = 0; j < v.size(); j++) {
                // printf("%d %d %d\n", v[j].idx, a[v[j].idx], v[j].t);
                bool ch = true;
                if (j > 0 && v[j].t == v[j - 1].t)
                    ch = false;
                if (j + 1 < v.size() && v[j].t == v[j + 1].t)
                    ch = false;
                if (ch) {
                    ans[v[j].idx]++;
                    break;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            printf("%d%c", ans[i], (i == n) ? '\n' : ' ');
        }
    }
    return 0;
}