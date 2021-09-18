#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

const int maxl = 1e5 + 10;
int x;

int main() {
    while (scanf("%d", &x) != EOF) {
        if (x < 40) {
            printf("%d\n", 40 - x);
        } else if (x < 70) {
            printf("%d\n", 70 - x);
        } else if (x < 90) {
            printf("%d\n", 90 - x);
        } else {
            printf("expert\n");
        }
    }

    return 0;
}
