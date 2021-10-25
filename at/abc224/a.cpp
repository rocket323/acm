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

char s[maxl];

int main() {
    scanf("%s", s);
    int n = strlen(s);
    if (s[n-1] == 'r')
        puts("er");
    else
        puts("ist");
    return 0;
}

