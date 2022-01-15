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

int f(int a, int b, int c) {
    return a * 100 + b * 10 + c;
}

int main() {
    int x;
    while (scanf("%d", &x) != EOF) {
        int c = x % 10;
        int b = x / 10 % 10;
        int a = x / 100;
        printf("%d\n", f(a, b, c) + f(b, c, a) + f(c, a, b));
    }
    return 0;
}
