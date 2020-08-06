#include <bits/stdc++.h>

using namespace std;

const int maxl = 1e5 + 10;

int t, n;
int a[maxl], b[maxl];
int d[maxl], fd[maxl];

void put(int a, set<int> &as, set<int> &bs) {
    if (bs.count(a)) {
        bs.erase(a);
    } else {
        as.insert(a);
    }
}

int solve() {
    if (a[1] != b[1])
        return -1;

    int l = 2;
    set<int> as, bs;

    d[a[1]] = 0;
    fd[0] = a[1];
    int dep = 1;
    while (l <= n) {
        int r = l;
        for (; r <= n; r++) {
            put(a[r], as, bs);
            put(b[r], bs, as);
            if (as.empty() && bs.empty())
                break;
        }

        fd[dep] = a[l];
        for (int i = l; i <= r; i++) {
            d[a[i]] = dep;
            // printf("%d ", a[i]);
        }
        dep++;
        // puts("\n");

        l = r + 1;
    }

    puts("Yes");
    for (int i = 1; i <= n; i++) {
        if (d[i] == 0) {
            printf("0");
        } else {
            int x = fd[d[i] - 1];
            printf("%d", x);
        }
        printf("%c", (i == n ? '\n' : ' '));
    }

    return 0;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &b[i]);

        int ans = solve();
        if (ans == -1) {
            puts("No");
        }
    }

    return 0;
}
