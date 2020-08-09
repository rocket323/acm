#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <assert.h>
#include <cmath>
#include <iostream>
using namespace std;
#define maxl 500010
const int mod = (1e9 + 7);
#define ll long long
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

ll n, h, w;
char s[maxl];
ll L[2*maxl], R[2*maxl], U[2*maxl], D[2*maxl];
ll sum_up[maxl], sum_down[maxl];

ll dr[4] = {0, 1, 0, -1};
ll dc[4] = {1, 0, -1, 0};

inline void Update(ll& a, ll b)
{
    if(a == -1) a = b;
}

ll Dir(char ch)
{
    switch(ch)
    {
        case 'R': return 0;
        case 'D': return 1;
        case 'L': return 2;
        case 'U': return 3;
        default: assert(false);
    }
}

ll Init()
{
	int n;
	long long sl;
    memset(L, -1, sizeof L);
    memset(R, -1, sizeof R);
    memset(U, -1, sizeof U);
    memset(D, -1, sizeof D);
    L[0] = R[0] = U[0] = D[0] = 0;

    ll r = 0, c = 0;
    ll ml = -1, mr = -1, mu = -1, md = -1;
    for(ll i = 0; i < n; ++i)
    {
        ll k = Dir(s[i]);
        r += dr[k];
        c += dc[k];

        if(c > 0) { Update(R[c], i + 1); mr = max(mr, c); }
        else { Update(L[-c], i + 1); ml = max(ml, -c); }

        if(r > 0) { Update(D[r], i + 1); md = max(md, r); }
        else { Update(U[-r], i + 1); mu = max(mu, -r); }
    }

    if(c != 0)
    {
        ll *arr = R;
        ll max_len = mr;
        if(c < 0) { arr = L; c = -c; max_len = ml; }
        for(ll loop = 0; max_len + c * loop < w; ++loop)
        {
            for(ll i = 1; i <= c; ++i)
            {
                arr[max_len + c * loop + i] = ((ll)n * (loop + 1) + arr[max_len - c + i]);
            }
        }
    }

    if(r != 0)
    {
        ll *arr = D;
        ll max_len = md;
        if(r < 0) { arr = U; r = -r; max_len = mu; }
        for(ll loop = 0; max_len + r * loop < h; ++loop)
        {
            for(ll i = 1; i <= r; ++i)
            {
                arr[max_len + r * loop + i] = ((ll)n * (loop + 1) + arr[max_len - r + i]);
            }
        }
    }

    memset(sum_up, 0, sizeof sum_up);
    memset(sum_down, 0, sizeof sum_down);
    for(ll i = 1; i <= h; ++i)
    {
        if(U[i] == -1 || sum_up[i-1] == -1) sum_up[i] = -1;
        sum_up[i] = (sum_up[i - 1] + U[i]) % mod;
    }
    for(ll i = 1; i <= h; ++i)
    {
        if(D[i] == -1 || sum_down[i-1] == -1) sum_down[i] = -1;
        sum_down[i] = (sum_down[i - 1] + D[i]) % mod;
    }

    return 0;
}

ll Cmp(ll x1, ll x2)
{
    if(x1 == -1)
	{
		if(x2 != -1) return 1;
		else return 0;
	}
    if(x2 == -1)
	{
		if(x1 != -1) return -1;
		else return 0;
	}
    return x1 - x2;
}

bool Check(ll x1, ll x2)
{
    if(x1 < 0 && x2 != 0) return 0;
    if(x2 < 0 && x1 != 0) return 0;
    return 1;
}

ll Process()
{
    ll r_seq = -1;
    for(ll r = 0; r < h; ++r)
    {
        ll t1 = U[r + 1], t2 = D[h - r];
        if(Cmp(t1, t2) < 0)
        {
            r_seq = r;
        }
    }

    ll ret = 0;
    for(ll c = 0; c < w; ++c)
    {
        ll t1 = L[c + 1], t2 = R[w - c];
        ll t;
        if(Cmp(t1, t2) < 0) t = t1;
        else t = t2;

        ll l = 0, r = r_seq, ans = -1;
        if(r >= 0)
        {
            while(l <= r)
            {
                ll mid = (l + r) / 2;
                if(Cmp(U[mid + 1],  t) <= 0)
                {
                    ans = mid;
                    l = mid + 1;
                }
                else
                    r = mid - 1;
            }
            if(sum_up[ans + 1] < 0) return -1;
            if(!Check(r_seq - ans, t)) return -1;
            ll tmp = (sum_up[ans + 1] + (ll)(r_seq - ans) * t % mod) % mod;
            ret = (ret + tmp) % mod;
        }

        l = 0, r = h - r_seq - 2, ans = -1;
        if(r >= 0)
        {
            ll dlen = r;
            while(l <= r)
            {
                ll mid = (l + r) / 2;
                if(Cmp(D[mid + 1], t) <= 0)
                {
                    ans = mid;
                    l = mid + 1;
                }
                else
                    r = mid - 1;
            }
            if(sum_down[ans + 1] < 0) return -1;
            if(!Check(dlen - ans, t)) return -1;
            ll tmp = (sum_down[ans + 1] + (ll)(dlen - ans) * t % mod) % mod;
            ret = (ret + tmp) % mod;
        }
    }

    return ret;
}

int main()
{
    while(cin >> n >> h >> w)
    {
		scanf("%s", s);
        Init();
        cout << Process() << endl;
    }

    return 0;
}

