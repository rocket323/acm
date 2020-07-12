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
const int maxl = 100010;
// const int mod = 163577857;
const int mod = 1e9 + 7;

int f[2600][2600];
int g[2600][2600];
int s[2600];
int n, p, sum[2600];

void add(int &a, int b) {
    a = (a + b) % mod;
}

int solve(int n, int p) {
    memset(f, 0, sizeof f);
    memset(sum, 0, sizeof sum);

    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= n; j++) {
            if (i < p)
                f[i][j] = f[i-1][j];

            int t2 = (j + 1) * j / 2;
            add(f[i][j], t2);
            add(f[i][j], sum[j-1]);
        } 
        memset(sum, 0, sizeof sum);
        for (int k = 1; k <= n; k++)
            add(sum[k], sum[k-1] + (ll)(k + 1) * f[i][k] % mod);
    }
    return f[p][n];
}

int gao(int n, int p) {
    memset(g, 0, sizeof g);
    memset(s, 0, sizeof s);
    for (int i = 1; i <= n; i++) {
        g[0][i] = 1;
        s[i] = (s[i-1] + (ll)g[0][i] * (i + 1)) % mod;
    }
    
    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= n; j++) {
            g[i][j] = (s[j-1] + g[i-1][j]) % mod;
        }

        s[0] = 0;
        for (int j = 1; j <= n; j++)
            s[j] = (s[j-1] + (ll)g[i][j] * (j + 1)) % mod;

        for (int j = 1; j <= n; j++)
            printf("%d ", s[j] + 1);
        puts("");
    }

    return g[p][n];
}

int main() {
    int t;
    gao(10, 10);
    /*
    for (int p = 0; p <= 10; p++) {
        for (int n = 1; n <= p + 10; n++) {
            printf("%d ", gao(n, p));
        }
        puts("");
    }
    */
    // scanf("%d", &t);
    // while (t--) {
    //     scanf("%d%d", &n, &p);
    //     int ans = gao(n, p);
    //     printf("%d\n", ans);
    // }

    return 0;
}

