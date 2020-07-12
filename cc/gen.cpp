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

int n, a[maxl];

int main() {
    srand(time(0));
    int t = 1;
    int n = 500;
    int m = 2;
    int q = 1020000;

    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int a = rand() % 100000;
            printf("%d ", a);
        }
        puts("");
    }

    return 0;
}

