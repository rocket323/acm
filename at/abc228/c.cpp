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

int n, k, a[maxl], x, b[maxl];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &x);
            a[i] += x;
            b[i] += x;
        }
    }
    sort(b, b + n);

    for (int i = 0; i < n; i++) {
        int idx = upper_bound(b, b + n, a[i] + 300) - b;
        int r = n - idx + 1;
        puts(r <= k ? "Yes" : "No");
    }

    return 0;
}

