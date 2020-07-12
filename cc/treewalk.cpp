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
const int maxl = 3010;
const int mod = 998244353;

int n, r, k;
vector<int> adj[maxl];
int f[maxl][maxl];

struct Matrix {
    Matrix(int n_, int v = 0) : n(n_) {
        memset(a, 0, sizeof a);
        for (int i = 1; i <= n; i++)
            a[i][i] = v;
    }

    int a[210][210];
    int n;
};

Matrix mul(const Matrix &a, const Matrix &b) {
    Matrix ans(n);

    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n; k++) {
            if (a.a[i][k] == 0) continue;

            for (int j = 1; j <= n; j++) {
                ans.a[i][j] = (ans.a[i][j] + (ll)a.a[i][k] * b.a[k][j]) % mod;
            }
        }
    }
    return ans;
}

Matrix pow(Matrix a, int x) {
    Matrix ans(n, 1);
    while (x) {
        if (x & 1) ans = mul(ans, a);
        x >>= 1;
        a = mul(a, a);
    }
    return ans;
}

void solve1() {
    Matrix mat(n);

    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            mat.a[v][u] = 1;
        }
    }

    auto mm = pow(mat, k);
    for (int i = 1; i <= n; i++) {
        int ans = mm.a[i][r];
        printf("%d%c", ans, i == n ? '\n' : ' ');
    }
}

void solve2() {
    memset(f, 0, sizeof f);
    f[0][r] = 1;

    for (int i = 0; i < k; i++) {
        for (int u = 1; u <= n; u++) {
            if (f[i][u] == 0)
                continue;

            for (int v : adj[u]) {
                f[i + 1][v] = (f[i + 1][v] + f[i][u]) % mod;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d%c", f[k][i], i == n ? '\n' : ' ');
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    scanf("%d%d", &r, &k);

    // solve1();
    // solve2();

    if (n <= 200) {
        solve1();
    } else {
        solve2();
    }

    return 0;
}

