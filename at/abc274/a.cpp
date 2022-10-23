#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%.3lf\n", b * 1.0 / a);
    return 0;
}