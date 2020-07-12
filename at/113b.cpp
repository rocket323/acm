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

int n, t, a;
int h[maxl];

int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%d%d", &t, &a);
        int dif = 0x7f7f7f7f, idx = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &h[i]);
            int tmp = abs(1000 * t - 6 * h[i] - a * 1000);
            if (idx == 0 || tmp < dif) {
                dif = tmp;
                idx = i;
            }
        }
        printf("%d\n", idx);
    }

    return 0;
}

