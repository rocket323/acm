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

int t, a, b, c;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &a, &b, &c);
        if (a == 7 || b == 7 || c == 7)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}

