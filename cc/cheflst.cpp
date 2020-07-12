#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int n, m, t, a[100][100];
bool f[2][50000][1024];
int maxm;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        maxm = 1024;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &a[i][j]);
                if (maxm < a[i][j])
                    maxm = a[i][j];
            }
        }

        memset(f, 0, sizeof f);
        f[0][0][0] = 1;
        int idx = 0;
        for (int i = 0; i < n; i++) {
            idx ^= 1;
            for (int j = 0; j < (1<<n); j++)
                for (int k = 0; k < maxm; k++)
                    f[idx][j][k] = 0;

            for (int j = 0; j < (1<<n); j++) {
                for (int k = 0; k < maxm; k++) {
                    if (f[idx^1][j][k] == 0)
                        continue;

                    for (int x = 0; x < n; x++) {
                        if (j & (1 << x))
                            continue;
                        int v = k ^ a[i][x];
                        f[idx][j|(1<<x)][v] = 1;
                    }
                }
            }
        }

        std::vector<int> ans;
        for (int k = 0; k < maxm; k++) {
            if (f[idx][(1<<n)-1][k])
                ans.push_back(k);
        }
        for (int i = 0; i < ans.size(); i++) {
            printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
        }
    }

    return 0;
}

