#include <bits/stdc++.h>
using namespace std;

const int maxl = 2e5 + 10;
int t, n, k, m, x;
vector<int> a[maxl];
int p[maxl];
unordered_map<int, int> st;
unordered_set<int> unempty;
int cnt;

void del(int l) {
    // printf("del %d %d\n", l, a[l][p[l]]);
    p[l]++;

    if (p[l] >= a[l].size()) {
        unempty.erase(l);
    } else {
        unempty.insert(l);
    }
}

void add(int l, int x) {
    // printf("add %d %d\n", l, x);
    auto iter = st.find(x);
    if (iter == st.end()) {
        st[x] = l;
        unempty.erase(l);
    } else {
        del(l);
        del(iter->second);
        cnt++;
        // printf("%d %d %d\n", x, l, iter->second);
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        st.clear();
        unempty.clear();
        for (int i = 1; i <= k; i++) {
            a[i].clear();
            scanf("%d", &m);
            for (int j = 0; j < m; j++) {
                scanf("%d", &x);
                a[i].push_back(x);
            }
        }
        for (int i = 1; i <= k; i++) {
            p[i] = 0;
            unempty.insert(i);
        }

        cnt = 0;
        while (!unempty.empty()) {
            auto tmp = unempty;
            for (int l : tmp) {
                int idx = p[l];
                int x = a[l][idx];
                add(l, x);
            }
        }
        // printf("%d\n", cnt);
        puts(cnt % 2 == 1 ? "Kelly" : "Nacho");
    }
    return 0;
}