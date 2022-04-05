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

int main() {

    int n, a, sum;
    while (scanf("%d", &n) != EOF) {
        sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            sum ^= a;
        }
        puts(sum ? "Yes" : "No");
    }

    return 0;
}