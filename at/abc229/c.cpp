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
const int maxl = 3e5 + 10;

struct Node {
    int a, b;
} e[maxl];

int n, w;

bool cmp(const Node &a, const Node &b) {
    return a.a > b.a;
}

int main() {
    scanf("%d%d", &n, &w);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &e[i].a, &e[i].b);
    }
    sort(e, e + n, cmp);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int k = min(w, e[i].b);
        ans = ans + (ll)e[i].a * k;
        w -= k;
    }
    cout << ans << endl;

    return 0;
}

