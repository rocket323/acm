#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int maxl = 1e5 + 10;
char s[1010], t[1010];

int main() {
    scanf("%s%s", s, t);
    bool f = false;
    int n = strlen(s);
    if (strcmp(s, t) == 0) {
        f = true;
    }
    for (int i = 0; i < n - 1; i++) {
        swap(s[i], s[i+1]);
        if (strcmp(s, t) == 0) {
            f = true;
            break;
        }
        swap(s[i], s[i+1]);
    }
    puts(f ? "Yes" : "No");
    return 0;
}

