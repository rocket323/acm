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

int x, y;

int main() {
    while (scanf("%d%d", &x, &y) != EOF) {
        printf("%d\n", x + y / 2);
    }

    return 0;
}

