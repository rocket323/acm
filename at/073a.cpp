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

int n;

int main() {
    while (scanf("%d", &n) != EOF) {
        bool flag = false;
        while (n > 0) {
            if (n % 10 == 9)
                flag = true;
            n /= 10;
        }
        puts(flag ? "Yes" : "No");
    }

    return 0;
}

