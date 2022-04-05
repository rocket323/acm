#include <stdio.h>
#define MaxL 100010
#define eps 1e-8
#define ll long long

ll n, L;
ll a[MaxL], Q[MaxL], head, tail, sum[MaxL];
ll f[MaxL];

void init()
{
    sum[0] = 0;
    for(ll i=1; i<=n; ++i)
    {
        scanf("%I64d", &a[i]);
        a[i] *= 1000;
        sum[i] = sum[i-1] + a[i];
    }
}

ll Max(ll a, ll b){ return (a>b)?a:b; }

ll K(ll i, ll j)
{
    //printf("%d %d\n", i, j);
    return (sum[i] - sum[j]) / (i-j);
}

void solve()
{
    ll ans = -1000000000;
    Q[head = 0] = 0;
    tail = 1;
    for(ll i=1; i<=n; ++i)
    {
        ll k = -1;
        if(Q[head]<=i-L) k = head;
        while(head+1<tail && Q[head+1]<=i-L) k = ++head;
        
        if(k!=-1)
        {
            k = Q[k];
            ans = Max(ans, (sum[i]-sum[k])/(i-k));
        }

        while(tail-head>1)
        {
            ll k1 = K(Q[tail-1], Q[tail-2]);
            ll k2 = K(i, Q[tail-1]);
            if(k1 > k2) tail--;
            else break;
        }
        Q[tail++] = i;
    }
    printf("%I64d\n", ans);
}

int main()
{
    scanf("%I64d%I64d", &n, &L);
    init();
    solve();
    return 0;
}

