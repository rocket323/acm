#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

char s[maxl];
int n, p[maxl], a[maxl];
vector<pair<int, int>> ans;
vector<int> adj[maxl];
int cnt[maxl], sum[maxl];

void dfs(int u) {
    for (int v : adj[u]) {
        dfs(v);
        cnt[u]++;
        sum[u] += sum[v];
    }
    sum[u] += cnt[u];
}

int main() {
    scanf("%s", s);
    n = strlen(s);

    p[1] = 0;
    int j = 0;
    adj[0].push_back(1);
    for (int i = 2; i <= n; i++) {
        while (j > 0 && s[j] != s[i - 1])
            j = p[j];
        if (s[j] == s[i - 1])
            j++;
        p[i] = j;
        adj[j].push_back(i);
    }

    dfs(0);

    int i = n;
    while (i > 0) {
        ans.push_back(make_pair(i, sum[i] + 1));
        i = p[i];
    }

    cout << ans.size() << endl;
    for (auto iter = ans.rbegin(); iter != ans.rend(); iter++)
        printf("%d %d\n", iter->first, iter->second);

    return 0;
}