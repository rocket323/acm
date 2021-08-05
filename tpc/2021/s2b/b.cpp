#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxl = 1e5 + 10;
const ll inf = 1e10;
unordered_map<int, pair<int, int>> mp;
ll c[maxl], d[maxl];
int n, k, x, t;

void add(int n, int k, int v) {
    auto iter = mp.find(v);
    if (iter != mp.end())
        return;
    mp[v] = make_pair(n, k);
}

void init() {
    add(0, 0, 1);
    c[0] = 1;
    c[1] = 1;
    for (int i = 2; i < maxl; i++) {
        int m = 0;
        d[i] = 1;
        d[0] = 1;
        for (int j = 1; j < i; j++) {
            d[j] = c[j - 1] + c[j];
            if (d[j] > inf) {
                break;
            }
            m = j;
            // printf("x %d %d %d %d\n", i, j, d[j], m);
            add(i, j, d[j]);
        }

        // printf("i %d %d\n", i, m);
        for (int j = 0; j <= m + 1; j++) {
            // printf("%d ", d[j]);
            c[j] = d[j];
        }
        // puts("");
    }
}

int main() {
    scanf("%d", &t);

    init();

    while (t--) {
        scanf("%d", &x);
        auto iter = mp.find(x);
        if (iter != mp.end()) {
            auto &p = iter->second;
            printf("%d %d\n", p.first, p.second);
        } else {
            printf("%d 1\n", x);
        }
    }
    return 0;
}
