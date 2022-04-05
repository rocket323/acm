#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f

char str[100];
int f[100][100], p[100][100], ans;

bool check(int a, int b, int c, int d)
{
    while(str[a] == '0' && a <= b) a++;
    while(str[c] == '0' && c <= d) c++;

    if(b - a < d -c) return 1;
    if(b - a > d - c) return 0;

    for(int i=a, j=c; i<=b && j<=d; ++i, ++j)
    {
        if(str[i] < str[j]) return 1;
        if(str[i] > str[j]) return 0;
    }
    return 0;
}

void out(int a, int b)
{
    for(int i=a; i<=b; ++i) printf("%c", str[i]);
}

void solve()
{
    int n = strlen(str), rec = -1;

    memset(f, 0x3f, sizeof f);
    f[n-1][n-1] = 1;
    for(int i=n-2; i>=0; --i)
    {
        if(str[i] == '0') f[i][n-1] = f[i+1][n-1];
        else f[i][n-1] = f[i+1][n-1] + 1;
    }

    ans = INF;

    for(int i=n-1; i>=0; --i)
    {
        for(int j=i; j<n; ++j)
        {
            for(int k=j; k<n; ++k)
            {
                if(!check(i, j, j+1, k)) continue;
                
                int x = f[j+1][k];
                if(x <= f[i][j])
                {
                    f[i][j] = x;
                    p[i][j] = k;
                }
            }

            if(i == 0 && f[i][j] <= ans)
            {
                ans = f[i][j];
                rec = j;
            }
        }
    }

    int a = 0, b = rec;
    while(true)
    {
        out(a, b);
        if(b < n-1)
        {
            int tmp = a;
            a = b + 1;
            b = p[tmp][b];
            printf(",");
        }
        else
        {
            puts("");
            break;
        }
    }
}

int main()
{
    while(scanf("%s", str) && !(strlen(str) == 1 && str[0] == '0'))
    {
        solve();
    }
    return 0;
}

