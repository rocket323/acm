#include <iostream>
#include <cmath>
#define Prime (1<<15-1)
#define ll long long
using namespace std;

struct node
{
    ll m, id;
    node * next;
};
node adj[Prime], memo[80000];

ll P, B, n, m, nn, d, y, rx, ry, mset;
ll bb[80000];

void gcd(ll a, ll b, ll& d, ll& x, ll& y)
{
    if(b==0){ d=a; x=1; y=0; }
    else
    {
        gcd(b, a%b, d, y, x);
        y -= (a/b)*x;
    }
}

ll mod(ll x, ll n){ return (x%n+n)%n; }

void insert(ll m, ll id)
{
    ll tmp = m%Prime;
    node* ptr = &memo[mset++];
    ptr->m = m;
    ptr->id = id;
    ptr->next = adj[tmp].next;
    adj[tmp].next = ptr;
}

ll find(ll m)
{
    ll tmp = m%Prime;
    node* ptr = adj[tmp].next;
    while(ptr)
    {
        if(ptr->m==m) return ptr->id;
        ptr = ptr->next;
    }
    return -1;
}

ll ppow(ll n)
{
    if(n==0) return 1;
    ll tmp = ppow(n/2);
    tmp = ((ll)tmp*(ll)tmp)%P;
    if(n&1) tmp = ((ll)tmp*(ll)B)%P;
    return tmp;
}

void init()
{
    for(ll i=0; i<Prime; ++i) adj[i].next = NULL;
    mset = 0;
    m = sqrt(P)+1;
    gcd(n, P, d, nn, y);
    
    nn = mod(nn, P);
    for(ll i=0; i<m; ++i)
    {
        bb[i] = ppow(P-1-i);
        insert(bb[i], i);
    }
}

void solve()
{
    rx=ry=-1;
    for(ll i=0; i<=m; ++i)
    {
        ll k=find(((ll)ppow(i*m)*(ll)nn)%P);
        if(k!=-1)
        {
            rx=i;
            ry=k;
            break;
        }
    }
    if(rx==-1) printf("no solution\n");
    else
    {
        ll res = mod(m*rx+ry, P-1);
        printf("%lld\n", res);
    }
}

int main()
{
    while(scanf("%lld%lld%lld", &P, &B, &n)!=EOF)
    {
        init();
        solve();
    }
    return 0;
}

