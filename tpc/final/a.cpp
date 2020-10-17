#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int maxl = 1e5 + 10;
using ll = long long;

int t, n, a[maxl];
ll b[maxl];
ll sum;
char s[maxl];
int p[5];
int pp[maxl];

bool cmp(int i, int j) {
    return a[i] > a[j];
}

bool cmp2(int i, int j) {
    return b[i] < b[j];
}

bool solve() {
    b[0] = b[1] = b[2] = 0;
    for (int i = 0; i < 3; i++) {
        p[i] = i;
    }

    for (int i = 0; i < n; i++) {
        int j = p[0];
        int u = pp[i];
        b[j] = b[j] +  a[u];
        if ((ll)b[j] * 2 > sum) {
            return false;
        }

        s[u] = '1' + p[0];
        sort(p, p + 3, cmp2);

        /*
        printf("%d %d\n", a[i], p[0]);
        printf("x ");
        for (int x = 0; x < 3; x++) {
            cout << b[x] << ' ';
        }
        puts("");
        */
    }

    s[n] = 0;
    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            sum += a[i];
            pp[i] = i;
        }
        // sort(a, a + n, cmp);
        sort(pp, pp + n, cmp);

        bool succ = solve();
        if (!succ) {
            puts("Impossible");
        } else {
            printf("%s\n", s);
        }
    }
    return 0;
}
