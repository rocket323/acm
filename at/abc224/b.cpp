#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;

int n, m, a[55][55];

bool gao() {
    for (int i1 = 0; i1 < n; i1++) {
        for (int i2 = i1 + 1; i2 < n; i2++) {
            for (int j1 = 0; j1 < m; j1++) {
                for (int j2 = j1 + 1; j2 < m; j2++) {
                    if (!(a[i1][j1] + a[i2][j2] <= a[i2][j1] + a[i1][j2])) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    puts(gao() ? "Yes": "No");
    return 0;
}

