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

int n;
char a[maxl], b[maxl];

int main() {
    scanf("%d", &n);
    scanf("%s", a);
    scanf("%s", b);
    bool yes = false;
    for (int i = 0; i < n; i++) {
        if (a[i] == 'o' && b[i] == 'o') {
            yes = true;
            break;
        }
    }
    puts(yes ? "Yes" : "No");
    return 0;
}