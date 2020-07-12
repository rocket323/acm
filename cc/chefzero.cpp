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
const int maxl = 1010;
const int mod = 1e9 + 7;

int n, m, k, a[maxl][maxl];
int b[maxl][maxl];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int d = n * m / k;
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--) {
        if ((n - 1 - i) % 2 == 1) {
            for (int j = 0; j < m; j++) {
                b[i][j] = cnt / d + 1;
                if (b[i][j] > k) b[i][j] = k;
                cnt++;
            }
        } else {
            for (int j = m - 1; j >= 0; j--) {
                b[i][j] = cnt / d + 1;
                if (b[i][j] > k) b[i][j] = k;
                cnt++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d%c", b[i][j], j == m - 1 ? '\n' : ' ');
        }
    }

    return 0;
}

