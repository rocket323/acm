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

int n, k, a[maxl], b[maxl];

int main() {
    scanf("%d%d", &n, &k);
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        mx = max(mx, a[i]);
    }
    bool flag = false;
    for (int i = 1; i <= k; i++) {
        int j;
        scanf("%d", &j);
        if (a[j] == mx)
            flag = true;
    }
    puts(flag ? "Yes" : "No");

    return 0;
}