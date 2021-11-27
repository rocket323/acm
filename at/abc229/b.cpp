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

char a[50], b[50];

bool gao() {
    int n = strlen(a), m = strlen(b);
    for (int i = 0; i < min(n, m); i++) {
        int x = a[n - 1 - i] - '0';
        int y = b[m - 1 - i] - '0';
        if (x + y > 9)
            return true;
    }
    return false;
}

int main() {
    scanf("%s%s", a, b);
    puts(gao() ? "Hard" : "Easy");
    
    return 0;
}

