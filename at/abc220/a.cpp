#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxl = 1e5 + 10;
int a, b, c;

int main() {
    scanf("%d%d%d", &a, &b, &c);
    int ans = -1;
    for (int i = a; i <= b; i++) {
        if (i % c == 0) {
            ans = i;
            break;
        }
    }
    printf("%d\n", ans);

    return 0;
}

