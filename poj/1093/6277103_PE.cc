#include <stdio.h>
#include <cstring>
#include <sstream>
#define INF 0x3f3f3f3f
#define two(x) ((x) * (x))
using namespace std;

char str[100], tmp[100], word[10010][100];
int f[10010][81], n, m, l[10010], p[10010][81];

void init()
{
    n = 0;
    while(gets(str))
    {
        if(!str[0]) break;
        istringstream in(str);

        while(in >> tmp)
        {
            strcpy(word[++n], tmp);
            l[n] = strlen(word[n]);
        }
    }
}

void solve()
{
    for(int i=0; i<=n; ++i)
        for(int j=0; j<=100; ++j)
            f[i][j] = INF;


    f[n][l[n]] = 0;
    f[n][m] = 500;

    for(int i=n-1; i>=1; --i)
    {
        //同在一行
        for(int j=l[i]+2; j<=m; ++j)
        {
            for(int k=j-l[i]-1; k>=1; --k)
            {
                int x = f[i+1][k] + two(j - k - l[i] - 1);
                if(x < f[i][j])
                {
                    f[i][j] = x;
                    p[i][j] = k;
                }
            }
        }
        //另起一行
        f[i][l[i]] = f[i+1][m];
        p[i][l[i]] = m;
    }

    //printf("%d\n", f[1][m]);

    int nw = m;
    for(int i=1; i<=n; ++i)
    {
        printf("%s", word[i]);
        if(p[i][nw] != m) for(int j=0; j<nw-p[i][nw]-l[i]; ++j) printf(" ");
        else puts("");
        nw = p[i][nw];
    }
    printf("\n\n");
}

int main()
{
    while(scanf("%d\n", &m), m)
    {
        init();
        solve();
    }
    return 0;
}

