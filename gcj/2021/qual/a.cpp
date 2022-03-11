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

int n, a[maxl];

int main() {
    int t;
    scanf("%d", &t);
    for (int x = 1; x <= t; x++) {
        scanf("%d", &n);
        int ans = 0;
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for (int i = 0; i < n - 1; i++) {
            int k = i;
            for (int j = i; j < n; j++) {
                if (a[j] < a[k])
                    k = j;
            }
            ans += (k - i + 1);
            reverse(a + i, a + k + 1);
        }
        printf("Case #%d: %d\n", x, ans);
    }
    return 0;
}
