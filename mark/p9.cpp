#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e5 + 10;
using ipair = pair<int, int>;
using ll = long long;
const int inf = 0x3f3f3f3f;

int t, n, m, a, b, c, k;
vector<pair<int, int>> adj[maxl];
int d[maxl], s[maxl], in[maxl], mn;

ll solve() {
    priority_queue<ipair, vector<ipair>, greater<ipair>> pq;
    int x = -1;
    for (int i = 1; i <= n; i++) {
        if (!s[i]) {
            x = i;
            break;
        }
    }
    if (x == -1) {
        if (n == 1) {
            return 0;
        } else if (n <= 2 && mn < inf) {
            return mn;
        } else {
            return -1;
        }
    }

    for (int i = 1; i <= n; i++)
        d[i] = inf;
    memset(in, 0, sizeof(in));

    pq.push({0, x});
    d[x] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (in[u]) {
            continue;
        }

        in[u] = true;
        for (auto &p : adj[u]) {
            int v = p.first;
            int w = p.second;
            if (!in[v] && d[v] > w) {
                d[v] = w;
                if (!s[v]) {
                    pq.push({d[v], v});
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (d[i] == inf)
            return -1;
        else
            ans += (ll)d[i];
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= n; i++)
            adj[i].clear();
        memset(s, 0, sizeof(s));
        mn = inf;
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &a, &b, &c);
            if (a != b) {
                adj[a].push_back({b, c});
                adj[b].push_back({a, c});
                mn = min(mn, c);
            }
        }
        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            int x;
            scanf("%d", &x);
            s[x] = 1;
        }

        ll ans = solve();
        if (ans == -1)
            puts("Impossible");
        else
            cout << ans << endl;
    }
    return 0;
}
