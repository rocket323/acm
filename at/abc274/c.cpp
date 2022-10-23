#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int n, a[maxl], c[maxl * 3];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        c[2 * i] = c[2 * i + 1] = c[a[i]] + 1;
        // printf("%d %d %d %d %d\n", i, 2 * i, 2 * i + 1, c[a[i]], a[i]);
    }
    for (int i = 1; i <= 2 * n + 1; i++) {
        printf("%d\n", c[i]);
    }

    return 0;
}