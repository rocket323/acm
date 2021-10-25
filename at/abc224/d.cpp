#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_set>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;

struct node {
    int st, d;
};

queue<node> q;
int n, m, p, v[10], a[10][10], x, y;
unordered_set<int> s;

int encode(int v[]) {
    int ans = 0;
    for (int i = 1; i <= 9; i++) {
        ans = ans * 10 + v[i];
    }
    return ans;
}

void decode(int st, int v[]) {
    for (int i = 9; i >= 1; --i) {
        v[i] = st % 10;
        st /= 10;
    }
}

void push(int v[], int d) {
    int st = encode(v);
    if (s.count(st))
        return;
    s.insert(st);
    node nd = {st, d};
    q.push(nd);
}

bool check(int v[]) {
    for (int i = 1; i <= 8; i++) {
        if (v[i] != i)
            return false;
    }
    return true;
}

void gao() {
    push(v, 0);

    while (!q.empty()) {
        node nd = q.front();
        q.pop();
        decode(nd.st, v);
        if (check(v)) {
            printf("%d\n", nd.d);
            return;
        }

        for (int i = 1; i <= 9; i++) {
            if (v[i] == 0) {
                for (int j = 1; j <= 9; j++) {
                    if (v[j] == 0 || !a[i][j])
                        continue;
                    swap(v[i], v[j]);
                    push(v, nd.d + 1);
                    swap(v[i], v[j]);
                }
            }
        }
    }

    puts("-1");
}

int main() {
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        a[x][y] = a[y][x] = 1;
    }
    for (int i = 1; i <= 8; i++) {
        scanf("%d", &p);
        v[p] = i;
    }
    gao();
    return 0;
}

