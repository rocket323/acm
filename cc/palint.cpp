#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int maxl = 1e5 + 10;
int t, n, x, a[maxl];
int ans, cnt;

map<int, pair<int, int>> mp;

void add(int v, int a) {
    auto iter = mp.find(v);
    if (iter == mp.end()) {
        mp[v] = make_pair(1, a);
    } else {
        mp[v].first++;
        mp[v].second += a;
    }

    if (mp[v].first > ans || mp[v].first == ans && mp[v].second < cnt) {
        ans = mp[v].first;
        cnt = mp[v].second;
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &x);
        mp.clear();
        ans = 0;
        cnt = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            add(a[i], 0);
            add(a[i] ^ x, 1);
        }
        if (x == 0) {
            ans /= 2;
            cnt = 0;
        }
        printf("%d %d\n", ans, cnt);
    }
    return 0;
}

