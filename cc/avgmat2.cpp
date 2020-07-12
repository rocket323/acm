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
const int maxl = 310;
const int mod = 1e9 + 7;

int t, n, m;
char s[maxl][maxl];
int cnt[maxl * 2];

int main() {
    scanf("%d", &t);
    while (t--) {
        memset(cnt, 0, sizeof cnt);
        scanf("%d%d", &n, &m);
        if (n > 50) break;
        for (int i = 0; i < n; i++)
            scanf("%s", s[i]);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s[i][j] == '0') continue;
                add(a0, i + j, j);
                add(a1, i - j, j);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s[i][j] == '0') continue;
            }
        }

        for (int i = 1; i <= n + m - 2; i++) {
            printf("%d%c", cnt[i] / 2, i == n + m - 2 ? '\n' : ' ');
        }
    }

    return 0;
}

