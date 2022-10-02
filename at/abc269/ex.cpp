#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;
using poly = vector<int>;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;
const int mod = 998244353;
const int G = 3;
const int maxk = 19;

int n;
int p[maxl], sz[maxl], GN[maxk][1 << (maxk - 1)];
vector<int> adj[maxl];

ll pow(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1)
            ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}

void init() {
    for (int p = 0, i = 1; p < maxk; p++, i <<= 1) {
        int g = pow(G, (mod - 1) / (i << 1));
        GN[p][0] = 1;
        for (int j = 1; j < i; j++) {
            GN[p][j] = (ll)GN[p][j - 1] * g % mod;
        }
    }
}

void ntt(vector<int> &a, vector<int> &R, int op) {
    int len = a.size();
    for (int i = 0; i < len; i++) {
        if (i < R[i])
            swap(a[i], a[R[i]]);
    }
    for (int p = 0, i = 1; i < len; i <<= 1, p++) {
        for (int j = 0; j < len; j += (i << 1)) {
            for (int k = 0; k < i; k++) {
                int x = a[j + k], y = (ll)GN[p][k] * a[j + k + i] % mod;
                a[j + k] = (x + y) % mod;
                a[j + k + i] = (x - y + mod) % mod;
            }
        }
    }
    if (op == 1)
        return;
    int inv = pow(len, mod - 2);
    if (len > 1)
        reverse(++a.begin(), a.end());
    for (int i = 0; i < len; i++) {
        a[i] = (ll)a[i] * inv % mod;
    }
}

vector<int> mul(vector<int> a, vector<int> b) {
    int n = a.size(), m = b.size();
    int len = 1, L = 0;
    while (len < n + m - 1) {
        len <<= 1;
        L++;
    }
    a.resize(len);
    b.resize(len);
    vector<int> R(len);
    for (int i = 0; i < len; i++) {
        R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
    }
    ntt(a, R, 1);
    ntt(b, R, 1);
    for (int i = 0; i < len; i++) {
        a[i] = (ll)a[i] * b[i] % mod;
    }
    ntt(a, R, -1);
    int l = n + m - 1;
    while (a[l - 1] == 0)
        l--;
    a.resize(l);
    return a;
}

poly operator+(const poly &a, const poly &b) {
    poly res(max(a.size(), b.size()));
    for (int i = 0; i < res.size(); i++)
        res[i] = ((i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0)) % mod;
    return res;
}

poly operator*(const poly &a, const poly &b) {
    return mul(a, b);
}

poly light(int);

void dfs(int u) {
    sz[u] = 1;
    for (int &v : adj[u]) {
        dfs(v);
        sz[u] += v;
        if (sz[v] > sz[adj[u][0]])
            swap(v, adj[u][0]);
    }
}

vector<poly> heavy(int u) {
    if (adj[u].empty())
        return {poly{1}};

    vector<poly> v;
    vector<poly> res = heavy(adj[u][0]);
    for (int i = 1; i < adj[u].size(); i++)
        v.push_back(light(adj[u][i]));

    while (v.size() >= 2) {
        vector<poly> w;
        for (int i = 0; i + 1 < v.size(); i += 2)
            w.push_back(v[i] * v[i + 1]);
        if (v.size() & 1)
            w.push_back(v.back());
        swap(v, w);
    }
    res.push_back(v.size() ? v.back() : poly{1});
    return res;
}

poly light(int u) {
    auto v = heavy(u);
    auto dc = [&](auto rc, int l, int r) -> pair<poly, poly> {
        if (l + 1 == r)
            return {poly{1}, v[l]};
        int m = (l + r) / 2;
        auto [L1, L2] = rc(rc, l, m);
        auto [R1, R2] = rc(rc, m, r);
        return {L1 * R2 + R1, L2 * R2};
    };
    auto [res1, res2] = dc(dc, 0, v.size());
    return res1 * poly{0, 1} + res2;
}

int main() {
    init();
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &p[i]);
        adj[p[i]].push_back(i);
    }
    dfs(1);
    auto ans = light(1);
    ans.resize(n + 1);
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return 0;
}