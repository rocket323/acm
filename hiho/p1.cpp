#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 1010;
const int mod = 1e9 + 7;

int n, m;
int p[maxl], q[maxl];
int sq[maxl];

int main() {

    while (scanf("%d%d", &n, &m) != EOF) {

        int ans = -1;
        int sa = -1, sb = -1;
        for (int i = 1; i <= n; ++i)
            scanf("%d", &p[i]);

        int x, a;
        scanf("%d", &x);
        memset(q, 0, sizeof q);
        for (int i = 0; i < x; ++i) {
            scanf("%d", &a);
            q[a + 1] = 1;
        }
        sq[0] = 0;
        for (int i = 1; i <= n; ++i)
            sq[i] = sq[i - 1] + q[i];

        for (int i = 1; i <= n; ++i) {
            if (q[i]) continue;

            for (int j = i + 1; j <= n; ++j) {
                if (q[j]) continue;

                bool flag = false;
                for (int k = j; k <= n; ++k) {
                    int x = sq[k] - sq[i - 1];
                    if (k - i + 1 - x == m) {
                        flag = true;
                        break;
                    }
                }

                if (flag) {
                    if (ans == -1 || p[i] + p[j] < ans) {
                        ans = p[i] + p[j];
                        sa = i;
                        sb = j;
                    }
                }
            }
        }
        printf("%d %d\n", sa - 1, sb - 1);
    }

    return 0;
}

