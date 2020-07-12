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

const int maxn = 100007;

int a[maxn];
int rk[maxn];
long long f[maxn][27];
bool vis[maxn];

void solve() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        rk[a[i]] = i;
        vis[a[i]] = 1;
    }
    rk[n + 1] = -1;

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            cout << 0 << endl;
            return;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            f[i][j] = 0;
        }
    }
    for (int j = 0; j < 26; j++) {
        f[0][j] = 1;
    }
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            if (f[i - 1][j] > 0) {
                int ch = j;
                if (rk[a[i] + 1] < rk[a[i - 1] + 1]) {
                    ch++;
                }
                for (int k = ch; k < 26; k++) {
                    f[i][k] += f[i - 1][j];
                }
            }
        }
    }
    
    long long sum = 0;
    for (int i = 0; i < 26; i++) {
        sum += f[n - 1][i];
    }
    
    cout << sum << endl;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        memset(vis, 0, sizeof vis);
        solve();
    }
}

