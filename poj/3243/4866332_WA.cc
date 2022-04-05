#include <iostream>
#include <cmath>
#include <algorithm>
#define Prime (1<<19)-1
#define LEN 100010
#define ll long long
using namespace std;

struct node
{
    ll num, idx;
    node * next;
}adj[Prime], memo[20*Prime];

ll A[LEN], L, mset;
ll P, B, N;
ll ans[LEN];

ll find(ll num)
{
    ll tmp = num % Prime;
    node * ptr = adj[tmp].next;
    while(ptr)
    {
        if(ptr->num == num) return ptr->idx;
        ptr = ptr->next;
    }
    return -1;
}

void toHash(ll num, ll idx)
{
    ll tmp = num % Prime;
    node * ptr = &memo[mset++];
    ptr->num = num;
    ptr->idx = idx;
    ptr->next = adj[tmp].next;
    adj[tmp].next = ptr;
}

void init()
{

    mset = 0;
    for(ll i=0; i<Prime; ++i) adj[i].next = NULL;

    L = (int)sqrt(P) + 1;
    A[0] = 1;
    toHash(A[0], 0);
    for(ll i=1; i<L; ++i)
    {
        A[i] = ((ll)A[i-1]*B) % P;
        if(find(A[i])==-1) toHash(A[i], i);
    }
}

ll pow(ll B, ll N, ll mod)
{
    if(N==0) return 1;
    ll mid = pow(B, N/2, mod);
    if(N & 1) return ((ll)mid * mid * B ) % mod;
    else return ((ll)mid * mid) % mod;
}

ll ex_gcd(ll a, ll b, ll& d, ll& x, ll& y)
{
    if(b==0){ d=a; x=1; y=0; }
    else
    {
        ex_gcd(b, a%b, d, y, x);
        y -= (ll)(a/b)*x;
    }
}

void go(ll a, ll P, ll& d, ll N, ll ans[])
{
    ll aa, y;
    ex_gcd(a, P, d, aa, y);
    
    if(N % d) { d = -1; return; }


    aa = (((ll)aa * (N/d) ) % P + P) % P;
    ans[0] = aa;
    for(ll i=1; i<d; ++i) ans[i] = (ans[i-1] + P/d) % P;
}

ll solve()
{
    ll ret = 0x7fffffffffffffffLL;
    ll bm = pow(B, L, P);
    ll a = 1, d;
    for(ll i=0; i<L; ++i)
    {
        go(a, P, d, N, ans);

        for(ll j=0; j<d; ++j)
        {
            ll k = find(ans[j]);
            if(k!=-1)
            {
                return (ll)i*L + k;
            }
        }

        a = ((ll)a * bm) % P;
    }
    return -1;
}

int main()
{
    while(scanf("%I64d%I64d%I64d", &B, &P, &N) && P)
    {
        B %= P; N %= P;
        init();
        ll k = solve();
        if(k==-1) printf("No Solution\n");
        else printf("%I64d\n", k);
    }
    return 0;
}

