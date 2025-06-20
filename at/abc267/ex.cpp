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

const int inf = 0x3f3f3f3f;
const int maxl = 2e6 + 10;
const int mod = 998244353;
const int G = 3;

using poly = vector<int>;

int n, m, a[maxl], c[11];
int frac[maxl], ifrac[maxl], inv[maxl];
pair<poly, poly> ps[11];

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
    frac[0] = 1;
    for (int i = 1; i < maxl; i++) {
        frac[i] = (ll)frac[i - 1] * i % mod;
    }
    ifrac[maxl - 1] = pow(frac[maxl - 1], mod - 2);
    for (int i = maxl - 2; i >= 0; i--) {
        ifrac[i] = (ll)ifrac[i + 1] * (i + 1) % mod;
    }
}

int C(int n, int m) {
    if (n < m || m < 0)
        return 0;
    return (ll)frac[n] * ifrac[m] % mod * ifrac[n - m] % mod;
}

void ntt(vector<int> &a, vector<int> &R, int op) {
    int len = a.size();
    for (int i = 0; i < len; i++) {
        if (i < R[i])
            swap(a[i], a[R[i]]);
    }
    for (int i = 1; i < len; i <<= 1) {
        int gn = pow(G, (mod - 1) / (i << 1));
        for (int j = 0; j < len; j += (i << 1)) {
            int g = 1;
            for (int k = 0; k < i; k++, g = (ll)g * gn % mod) {
                int x = a[j + k], y = (ll)g * a[j + k + i] % mod;
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
    return a;
}

poly operator+(const poly &a, const poly &b) {
    poly res(max(a.size(), b.size()));
    for (int i = 0; i < res.size(); i++)
        res[i] = ((i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0)) % mod;
    return res;
}

pair<poly, poly> operator+(const pair<poly, poly> &a, const pair<poly, poly> &b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

pair<poly, poly> solve(int l, int r) {
    if (l == r) {
        return move(ps[l]);
    }

    int mid = (l + r) / 2;
    auto &&a = solve(l, mid);
    auto &&b = solve(mid + 1, r);
    return make_pair(mul(a.first, b.first) + mul(a.second, b.second), mul(a.first, b.second) + mul(a.second, b.first));
}

void gao(int x, int cnt) {
    int size = min(x * cnt + 1, m + 1);
    ps[x].first.resize(size);
    ps[x].second.resize(size);
    for (int i = 0; i <= cnt; i++) {
        ll j = (ll)i * x;
        if (j >= size)
            break;
        auto &&p = (i & 1) ? ps[x].second : ps[x].first;
        p[j] = C(cnt, i);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        c[a[i]]++;
    }

    init();
    for (int i = 1; i <= 10; i++) {
        gao(i, c[i]);
    }
    auto ans = solve(1, 10);
    if (ans.second.size() <= m)
        puts("0");
    else
        printf("%d\n", (ans.second)[m]);
    return 0;
}