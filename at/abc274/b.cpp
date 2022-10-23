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

int n, m, f[1010];
char s[1010];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        for (int j = 0; j < m; j++) {
            if (s[j] == '#')
                f[j]++;
        }
    }
    for (int j = 0; j < m; j++) {
        printf("%d%c", f[j], j == m - 1 ? '\n' : ' ');
    }
    return 0;
}