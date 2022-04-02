#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e5 + 10;

int t, n, s[maxl];

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &s[i]);
        sort(s, s + n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] >= ans + 1)
                ans++;
        }
        printf("Case #%d: %d\n", tc, ans);
    }
    return 0;
}