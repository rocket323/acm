#include <stdio.h>
#include <sstream>
#include <cstring>
#include <iostream>
using namespace std;

int g[101][101], top, n, t;
char T[101][21];
int I[101][101], A[101], B[101][101];
int ret[101];

int getID(char ch[])
{
    for(int i=1; i<=top; ++i)
    {
        if(strcmp(T[i], ch)==0) return i;
    }
    top++;
    strcpy(T[top], ch);
    return top;
}

void init()
{
    top = 0;
    char S[1000];
    int k;
    scanf("%d%d\n", &n, &t);
    memset(g, 0, sizeof g);
    for(int i=1; i<=n; ++i)
    {
        gets(S);
        istringstream in(S);
        char a[21], b[21];
        in >> a;
        int x = getID(a);
        in >> A[x];
        in >> k;
        for(int j=1; j<=k; ++j)
        {
            in >> b;
            int y = getID(b);
            g[x][y] ^= 1;
        }
        g[x][x] ^= 1;
    }
}

void matrix(int c[][101], int a[][101], int b[][101])
{
    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=n; ++j)
        {
            c[i][j] = 0;
            for(int k=1; k<=n; ++k)
            {
                c[i][j] = (c[i][j] + (a[i][k] * b[k][j])) % 2;
            }
        }
    }
}

void pow(int A[][101], int n)
{
    if(n==0)
    {
        memcpy(A, I, sizeof I);
        return;
    }
    int tmp[101][101];
    pow(A, n/2);
    matrix(tmp, A, A);
    if(n&1) matrix(A, tmp, g);
    else matrix(A, tmp, I);
}

void solve()
{
    int ans = 0;

    memset(I, 0, sizeof I);
    for(int i=0; i<=n; ++i) I[i][i] = 1;

    pow(B, t-1);

    /*
    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=n; ++j) printf("%d ", g[i][j]);
        printf("\n");
    }*/

    for(int i=1; i<=n; ++i)
    {
        ret[i] = 0;
        for(int j=1; j<=n; ++j)
        {
            ret[i] += (A[j] & 1) * B[j][i];
        }
        ans += ret[i] % 2;
    }
    printf("%d\n", ans);
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        init();
        solve();
    }
    return 0;
}
