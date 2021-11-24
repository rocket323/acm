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
const int maxl = 205;

int t, n, k, a[maxl], lft[maxl], b[maxl];
int m, f[maxl], c[maxl];

int lis2(int b[]) {
    for (int i = 0; i < n; i++) {
        c[i] = b[i + 1];
        f[i] = inf;
    }
    int pos = 0;
    f[0] = c[0];
    for (int i = 1; i < n; i++) {
        if (c[i] >= f[pos])
            f[++pos] = c[i];
        else
            f[lower_bound(f, f + pos + 1, c[i]) - f] = c[i];
    }
    for (int i = 0; i < n; i++)
        printf("%d ", c[i]);
    puts("");
    printf("ans: %d\n", pos + 1);
    return pos + 1;
}

int lis(int b[]) {
    f[1]=b[1];
    int len=1;
    for(int i=2;i<=n;i++)
    {
        if(b[i] >= f[len])
        f[++len] = b[i];
        else
        {
            int j = upper_bound(f+1, f+len+1, b[i]) - f;
            f[j] = b[i];
        }
    }
    // for (int i = 1; i <= n; i++)
    //     printf("%d ", b[i]);
    // puts("");
    // printf("ans: %d\n", len);
    return len;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        m = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            b[i] = a[i];
            lft[m++] = a[i];
        }

        for (int i = 1; i <= n; i++) {
            sort(lft, lft + m);
            for (int j = 0; j < m; j++) {
                b[i] = lft[j];
                int p = i + 1;
                for (int x = 0; x < m; x++) {
                    if (x != j)
                        b[p++] = lft[x];
                }
                int l = lis(b);
                if (l > k) {
                    p = i + 1;
                    for (int x = m-1; x >= 0; x--) {
                        if (x != j)
                            b[p++] = lft[x];
                    }
                    int low = lis(b);
                    if (low <= k) {
                        swap(lft[j], lft[m - 1]);
                        m--;
                        break;
                    }
                } else if (l == k || j == m - 1) {
                    swap(lft[j], lft[m - 1]);
                    m--;
                    break;
                }
            }
        }

        // puts("====");
        int x = lis(b);
        if (x == k) {
            for (int i = 1; i <= n; i++) {
                printf("%d%c", b[i], i == n ? '\n' : ' ');
            }
        } else {
            puts("-1");
        }
    }
    return 0;
}

