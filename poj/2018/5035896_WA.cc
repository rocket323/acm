#include <stdio.h>
#define MaxL 100010

int n, L;
int a[MaxL], Q[MaxL], head, tail, sum[MaxL];
double f[MaxL];

void init()
{
    sum[0] = 0;
    for(int i=1; i<=n; ++i)
    {
        scanf("%d", &a[i]);
        sum[i] = sum[i-1] + a[i];
    }
}

double Max(double a, double b){ return (a>b)?a:b; }

double K(int i, int j)
{
    return (sum[i] - sum[j]) / (i-j+0.0);
}

void solve()
{
    double ans = -1e20;
    Q[head = 0] = 0;
    tail = 1;
    for(int i=1; i<=n; ++i)
    {
        int k = -1;
        while(head<tail && Q[head]<=i-L) k = head++;
        if(head<tail && Q[head]>i-L) head--;

        if(k!=-1)
        {
            k = Q[k];
            ans = Max(ans, (sum[i]-sum[k])/(i-k+0.0));
        }

        while(tail-head>1)
        {
            double k1 = K(Q[tail-1], Q[tail-2]);
            double k2 = K(i, Q[tail-1]);
            if(k1 > k2) tail--;
            else break;
        }
        Q[tail++] = i;
    }
    printf("%.0f\n", ans * 1000);
}

int main()
{
    scanf("%d%d", &n, &L);
    init();
    solve();
    return 0;
}

