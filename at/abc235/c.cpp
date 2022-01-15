#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int n, a[maxl], q;
unordered_map<int, vector<int>> mp;

int gao(int x, int k) {
    auto iter = mp.find(x);
    if (iter == mp.end())
        return -1;
    auto &&v = iter->second;
    if (k > v.size())
        return -1;
    return v[k - 1];
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        mp[a[i]].push_back(i);
    }
    for (int i = 0; i < q; i++) {
        int x, k;
        scanf("%d%d", &x, &k);
        printf("%d\n", gao(x, k));
    }
    return 0;
}
