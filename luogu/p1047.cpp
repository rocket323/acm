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
const int maxl = 1e5 + 10;

int l, m, u, v, a[maxl];

int main() {
    scanf("%d%d", &l, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        for (int j = u; j <= v; j++)
            a[j] = 1;
    }
    int ans = 0;
    for (int i = 0; i <= l; i++) {
        if (!a[i])
            ans++;
    }
    printf("%d\n", ans);

    return 0;
}
