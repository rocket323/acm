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
char s1[maxl], s2[maxl], s3[maxl], t[maxl];

int main() {
    while (scanf("%s", s1) != EOF) {
        scanf("%s", s2);
        scanf("%s", s3);
        scanf("%s", t);
        for (int i = 0; t[i]; i++) {
            if (t[i] == '1') {
                printf("%s", s1);
            } else if (t[i] == '2') {
                printf("%s", s2);
            } else if (t[i] == '3') {
                printf("%s", s3);
            }
        }
        puts("");
    }

    return 0;
}
