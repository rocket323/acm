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

int t, n, p, a[maxl];

int main() {
    scanf("%d", &t);
    while (t--) {
        int easy = 0, hard = 0;
        scanf("%d%d", &n, &p);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            if (a[i] >= p / 2)
                easy++;
            if (a[i] <= p / 10)
                hard++;
        }
        if (easy == 1 && hard == 2)
            printf("yes\n");
        else
            printf("no\n");
    }

    return 0;
}

