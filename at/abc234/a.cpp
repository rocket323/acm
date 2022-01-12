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

int f(int x) {
    return x * x + 2 * x + 3;
}

int main() {
    int t;
    while (scanf("%d", &t) != EOF) {
        int x = f(f(f(t) + t) + f(f(t)));
        printf("%d\n", x);
    }
    return 0;
}
