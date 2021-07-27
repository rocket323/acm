#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e4;
using ipair = pair<int, int>;
using ll = long long;

int n, m, k, q, t;
int a[maxl], b[maxl];
int g[1010][1010];
char s[10];
ll ans;
int mp[10100000 + 10];
int st[3000000];
int top;
vector<ipair> rocks;

void getrc(char ch, int &dr, int &dc) {
    if (ch == 'U') {
        dr = 1, dc = 0;
    } else if (ch == 'D') {
        dr = -1, dc = 0;
    } else if (ch == 'L') {
        dr = 0, dc = 1;
    } else {
        dr = 0, dc = -1;
    }
}

int idx(int r, int c) {
    return (r + 1005) * 2020 + c + 1005;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d%d", &n, &m, &k, &q);
        ans = 0;
        rocks.clear();
        top = 0;
        for (int i = 0; i < k; i++) {
            scanf("%d%d", &a[i], &b[i]);
            g[a[i]][b[i]] = 1;
        }

        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j <= m + 1; j++) {
                if (g[i][j] == 1 || i == 0 || i == n + 1 || j == 0 || j == m + 1) {
                    rocks.push_back({i, j});
                } else {
                    int xx = idx(i, j);
                    mp[xx] = 1;
                    st[top++] = xx;
                }
            }
        }

        for (int i = 0; i < q; i++) {
            scanf("%s", s);
            int dr = 0, dc = 0;
            getrc(s[0], dr, dc);

            ans = 0;
            for (auto &&r : rocks) {
                int rr = r.first + dr;
                int cc = r.second + dc;
                r.first = rr;
                r.second = cc;
                int xx = idx(rr, cc);
                auto &it = mp[xx];
                if (it > 0) {
                    int yy = idx(rr + dr, cc + dc);
                    int &p = mp[yy];
                    ll sum = it + p;
                    if (p > 0) {
                        ans += sum;
                    } else {
                        st[top++] = yy;
                    }
                    p = sum;
                    it = 0;
                }
            }
            cout << ans << endl;
        }

        for (int i = 0; i < k; i++) {
            g[a[i]][b[i]] = 0;
        }

        for (int i = 0; i < top; i++) {
            mp[st[i]] = 0;
        }
        top = 0;
    }
    return 0;
}
