#include <stdio.h>
#include <cstring>
#define max(a,b) ((a>b)?a:b)

int A[160][11], f[160][60000];
int c[11], ans, n, m, k;
int t[60000][11];

void init()
{
    scanf("%d%d%d", &n, &m, &k);
    memset(A, 0, sizeof A);
    for(int i=0; i<k; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        A[x][y-1] = 1;
    }
}

void dfs1(int pos, int mask, int num)
{
    if(pos == m)
    {
        f[2][mask] = max(f[2][mask], num);
        return;
    }
    //nothing
    int add;
    if(A[2][pos] == 1) add = 2;
    else if(A[1][pos] == 1) add = 1;
    else add = 0;
    dfs1(pos+1, mask + add * c[pos], num);
    //2 x 3
    if(pos <= m - 3 && !A[1][pos] && !A[1][pos+1] && !A[1][pos+2] && !A[2][pos] && !A[2][pos+1] && !A[2][pos+2])
        dfs1(pos+3, mask + 2 * (c[pos] + c[pos+1] + c[pos+2]), num+1);
}

void dfs(int row, int now, int pos, int mask, int num)
{
    if(pos == m)
    {
        f[row+1][mask] = max(f[row+1][mask], f[row][now] + num);
        return;
    }
    //nothing
    int add;
    if(A[row+1][pos] == 1) add = 2;
    else if(t[now][pos] == 2) add = 1;
    else add = 0;
    dfs(row, now, pos+1, mask + add * c[pos], num); 
    
    //2 x 3
    if(pos <= m - 3 && t[now][pos]<=1 && t[now][pos+1]<=1 && t[now][pos+2]<=1
            && !A[row+1][pos] && !A[row+1][pos+1] && !A[row+1][pos+2])
        dfs(row, now, pos+3, mask + 2 * (c[pos] + c[pos+1] + c[pos+2]), num + 1);

    //3 x 2
    if(pos <= m - 2 && t[now][pos]<=0 && t[now][pos+1]<=0 
            && !A[row+1][pos] && !A[row+1][pos+1]) 
        dfs(row, now, pos+2, mask + 2 * (c[pos] + c[pos+1]), num + 1);
}

int solve()
{
    if(n < 2) return 0;

    memset(f, -1, sizeof f);


    ans = 0;
    dfs1(0, 0, 0);
    //for(int i=0; i<c[m]; ++i) printf("n %d %d\n", i, f[2][i]);

    for(int i=2; i<n; ++i)
    {
        for(int j=0; j<c[m]; ++j)
        {
            //printf("%d %d %d\n", i, j, f[i][j]);
            if(f[i][j] == -1) continue;

            //printf("%d %d %d\n", i, j, f[i][j]);

            dfs(i, j, 0, 0, 0);
        }
    }

    for(int i=0; i<c[m]; ++i) ans = max(ans, f[n][i]);

    return ans;
}

int check(int n, int p)
{
    for(int i=0; i<p; ++i) n /= 3;
    return n % 3;
}

int main()
{

    c[0] = 1;
    for(int i=1; i<=10; ++i) c[i] = c[i-1] * 3;

    for(int i=0; i<c[10]; ++i)
        for(int j=0; j<10; ++j)
            t[i][j] = check(i, j);

    int t;
    scanf("%d", &t);
    while(t--)
    {
        init();
        printf("%d\n", solve());
    }
    return 0;
}

