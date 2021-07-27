#include <bits/stdc++.h>
using namespace std;

struct node {
    int r, c, d;
};

int n, m, r, c;
int a[500][500];
queue<node> q;
int dr[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
int dc[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

void push(int r, int c, int d) {
    if (a[r][c] == -1) {
        node nd = {r, c, d};
        q.push(nd);
        a[r][c] = d;
    }
}

void solve() {
    memset(a, -1, sizeof(a));
    push(r, c, 0);

    while (!q.empty()) {
        node &nd = q.front();
        q.pop();
        for (int i = 0; i < 8; i++) {
            int rr = nd.r + dr[i];
            int cc = nd.c + dc[i];
            if (rr >= 1 && rr <= n && cc >= 1 && cc <= m) {
                push(rr, cc, nd.d + 1);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%-5d", a[i][j]);
        }
        puts("");
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &r, &c);
    solve();
    return 0;
}
