#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

const int maxl = 3e5 + 10;
const int mod = 1e9 + 7;
using ll = long long;

int n, p;
int sz[maxl], son[maxl];
char str[maxl];
string s[maxl], t;
ll ans;
vector<int> adj[maxl];

vector<int> suf_s[maxl];
vector<int> suf, pre;

unordered_map<int, int> cnt[maxl];

int pow(int a, int n) {
    int ans = 1, t = a;
    while (n) {
        if (n & 1)
            ans = (ll)ans * t % mod;
        t = (ll)t * t % mod;
        n >>= 1;
    }
    return ans;
}

void dfs1(int u) {
    sz[u] = 1;
    son[u] = 0;

    for (int v : adj[u]) {
        dfs1(v);
        sz[u] += sz[v];
        if (son[u] == 0 || sz[v] > sz[son[u]])
            son[u] = v;
    }
}

void add(int u, int len, int h, int val) {
    int hh = h;
    for (int i = 0; i < s[u].length(); i++) {
        hh = ((ll)hh * 233 + s[u][i]) % mod;
        cnt[len + i + 1][hh] += val;
    }

    for (int v : adj[u]) {
        add(v, len + s[u].length(), hh, val);
    }
}

void dfs2(int u, int keep) {
    for (int v : adj[u]) {
        if (v != son[u])
            dfs2(v, 0);
    }

    if (son[u])
        dfs2(son[u], 1);

    for (int v : adj[u]) {
        if (v != son[u])
            add(v, 0, 0, 1);
    }

    // answer
    int tl = t.length();
    int hh = 0;
    if (s[u].length() >= tl) {
        for (int i = 0; i < tl; i++) {
            hh = ((ll)hh * 233 + s[u][i]) % mod;
        }
    }

    int pp = pow(233, tl - 1);
    for (int i = 0; i < s[u].length(); i++) {
        int l = s[u].length() - i;
        if (l >= t.length()) {
            if (hh == suf[0]) {
                ans++;
            }

            if (i + tl < s[u].length()) {
                int x = (ll)s[u][i] * pp % mod;
                hh = (hh - x + mod) % mod;
                hh = ((ll)hh * 233 + s[u][i + tl]) % mod;
            }
            continue;
        }

        if (suf_s[u][i] == pre[l - 1]) {
            int len = tl - l;
            int h2 = suf[l];
            printf("%d %d %d\n", u, i, cnt[len][h2]);
            if (cnt[len][h2] > 0) {
            }
            ans = (ans + cnt[len][h2]) % mod;
        }
    }

    if (!keep) {
        for (int v : adj[u]) {
            add(v, 0, 0, -1);
        }
    }
}

void calcSuf(const string &s, vector<int> &suf) {
    suf.resize(s.length() + 10);
    suf[0] = 0;
    int n = s.length();
    for (int i = 0; i < n; i++) {
        suf[0] = ((ll)suf[0] * 233 + s[i]) % mod;
    }

    for (int i = 1; i < n; i++) {
        int p = s.length() - i;
        int x = (ll)s[i - 1] * pow(233, p) % mod;
        suf[i] = (suf[i - 1] - x + mod) % mod;
    }
}

void calcPre(const string &s, vector<int> &pre) {
    pre.resize(s.length() + 10);
    pre[0] = s[0];
    for (int i = 1; i < s.length(); i++) {
        pre[i] = ((ll)pre[i - 1] * 233 + s[i]) % mod;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d%s", &p, str);
        adj[p].push_back(i);
        s[i] = str;
        calcSuf(s[i], suf_s[i]);
    }
    scanf("%s", str);
    t = str;

    calcSuf(t, suf);
    calcPre(t, pre);

    ans = 0;
    dfs1(1);
    dfs2(1, 0);

    cout << ans << endl;

    return 0;
}
