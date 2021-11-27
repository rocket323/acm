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

char s[10][10];

int main() {
    for (int i = 0; i < 2; i++)
        scanf("%s", s[i]);
    bool f = true;
    if (s[0][0] == '.' && s[1][1] == '.')
        f = false;
    if (s[0][1] == '.' && s[1][0] == '.')
        f = false;
    puts(f ? "Yes": "No");

    return 0;
}

