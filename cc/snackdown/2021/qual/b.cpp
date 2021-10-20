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

int t, a[maxl];

int main() {
    scanf("%d", &t);
    while (t--) {
        memset(a, 0, sizeof a);
        int x;
        for (int i = 0; i < 5; i++) {
            scanf("%d", &x);
            a[x]++;
        }
        if (a[1] == a[2])
            puts("DRAW");
        else if (a[1] > a[2])
            puts("INDIA");
        else
            puts("ENGLAND");
    }
    return 0;
}

