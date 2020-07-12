#include <stdio.h>
#include <cstring>

int getWeek(int y, int m, int d) {
    if (m == 1 || m == 2) {
        m += 12;
        y--;
    }
    return (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
}

bool check(int y, int m, int d) {
    bool yun = false;
    if (y % 4 == 0 && y % 100 != 0) yun = true;
    if (y % 400 == 0) yun = true;

    if (m == 2 && d == 29) {
        return yun;
    } else {
        return true;
    }
}

int main() {
    int t, y, m, d;
    char s[100];

    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        y = m = d = 0;
        for (int i = 0; i < 4; ++i)
            y = y * 10 + (s[i] - '0');
        for (int i = 5; i < 7; ++i)
            m = m * 10 + (s[i] - '0');
        for (int i = 8; i < 10; ++i)
            d = d * 10 + (s[i] - '0');

        int week = getWeek(y, m, d);

        for (int i = y+1; ; ++i) {
            if (!check(i, m, d)) continue;
            int tmp = getWeek(i, m, d);
            if (tmp == week) {
                printf("%d\n", i);
                break;
            }
        }
    }

    return 0;
}

