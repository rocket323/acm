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
const int maxl = 500;
const int mod = 998244353;

int n, m, q;
int t[250];
std::vector<int> adj[maxl];
int p[maxl];
int a[maxl], b[maxl], ans[maxl];
int rev[maxl];

struct Matrix {
    int a[maxl][maxl];
    void init() {
        memset(a, 0, sizeof a);
        for (int i = 1; i <= 2 * n; i++)
            a[i][i] = 1;
    }
};

Matrix mat;
Matrix pp[21];

Matrix mul(const Matrix &a, const Matrix &b) {
    Matrix ans;
    for (int i = 1; i <= 2 * n; i++)
        for (int j = 1; j <= 2 * n; j++)
            ans.a[i][j] = 0;

    for (int i = 1; i <= 2 * n; i++) {
        for (int k = 1; k <= 2 * n; k++) {
            if (a.a[i][k] == 0) continue;

            for (int j = 1; j <= 2 * n; j++) {
                ans.a[i][j] = (ans.a[i][j] + (ll)a.a[i][k] * b.a[k][j]) % mod;
            }
        }
    }
    return ans;
}

Matrix pow(Matrix a, int n) {
    Matrix ans;
    ans.init();
    int t = 1;
    while (n) {
        if (n & 1) ans = mul(ans, pp[t]);
        n >>= 1;
        t++;
        // a = mul(a, a);
    }
    return ans;
}

void init() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &t[i]);
    }
    scanf("%d", &q);

    rev[1] = 1;
    for (int i = 2; i <= n; i++) {
        rev[i]=(long long)(mod - mod / i) * rev[mod % i] % mod;
    }
}

void dfs(int u, int pre) {
    p[u] = pre;
    for (int v : adj[u]) {
        if (v != pre)
            dfs(v, u);
    }
}

void solve() {
    dfs(1, -1);

    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    memset(ans, 0, sizeof ans);
    memset(mat.a, 0, sizeof mat.a);
    a[1] = 1;

    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            if (v == p[u]) {
                mat.a[u + n][v + n] = 1;
            } else {
                if (u == 1) { // root
                    mat.a[u + n][v] = rev[adj[u].size()];
                    mat.a[u][v] = rev[adj[u].size()];
                }
                else // inner
                    mat.a[u][v] = rev[adj[u].size() - 1];
            }
            // leaf
            if (adj[u].size() == 1) {
                mat.a[u][p[u] + n] = 1;
                mat.a[u + n][p[u] + n] = 1;
            }
        }

        mat.a[u][u] = 1;
        mat.a[u + n][u + n] = 1;
    }

    pp[0].init();
    pp[1] = mat;
    for (int i = 2; i <= 20; i++)
        pp[i] = mul(pp[i - 1], pp[i - 1]);

    for (int x = 0; x < m; x++) {
        int cnt = q - t[x];
        if (cnt < 0) continue;
        auto &&tmp = pow(mat, q - (t[x]));

        for (int i = 1; i <= 2 * n; i++) {
            b[i] = 0;
            for (int j = 1; j <= 2 * n; j++) {
                b[i] = (b[i] + (ll)a[j] * tmp.a[j][i]) % mod;
            }
        }

        for (int i = 1; i <= 2 * n; i++)
            ans[i] = (ans[i] + b[i]) % mod;
    }

    for (int i = 1; i <= n; i++) {
        printf("%d%c", (ans[i] + ans[i + n]) % mod, i == n ? '\n' : ' ');
    }
}

int main() {
    init();
    solve();
    return 0;
}

