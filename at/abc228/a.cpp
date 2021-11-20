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

int main() {
    int s, t, x;
    while (scanf("%d%d%d", &s, &t, &x) != EOF) {
        if (t < s)
            t += 24;

        if (x >= s && x < t) {
            puts("Yes");
        } else if (x + 24 >= s && x + 24 < t) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}

