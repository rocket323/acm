#include <bits/stdc++.h>
using namespace std;

const int maxl = 205;
int n, k, a[maxl], t, idx;
bool s, win;
int cnt[maxl];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        memset(cnt, 0, sizeof(cnt));
        s = true;
        idx = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            a[i + n] = a[i];
            if (i > 1 && a[i] != a[i - 1])
                s = false;
        }

        n *= 2;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (j == a[i])
                    cnt[j]++;
                else
                    cnt[j] = 0;
            }
            if (cnt[a[i]] >= k) {
                idx = i;
                break;
            }
        }

        if (idx > 0) {
            printf("%d %d\n", idx, a[idx]);
        } else {
            if (s) {
                printf("%d %d\n", k, a[1]);
            } else {
                printf("INF\n");
            }
        }
    }
}
