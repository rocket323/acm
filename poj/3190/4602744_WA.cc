#include <iostream>
#include <algorithm>
#include <set>
#define MaxN 50010
using namespace std;

struct node
{
    int s, f, lv;
}T[MaxN];

set< pair<int, int> > S;

int N, m, res = N;
int par[MaxN], tmp[MaxN];

bool cmp(node A, node B){ return A.f<B.f; }

void init()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
    {
        scanf("%d%d", &T[i].s, &T[i].f);
        T[i].lv = i;
    }
    sort(T, T+N, cmp);
}

bool pop(int idx)
{
    if(m==0) return 0;
    set<pair<int, int> > :: iterator it;

    it = S.lower_bound(make_pair(T[idx].s, 1));
    if(it==S.begin()) return 0;

    it--;
    tmp[T[idx].lv] = it->second;
    S.erase(it);
    S.insert(make_pair(T[idx].f, tmp[T[idx].lv]));
    return 1;
}

bool check(int sz)
{
    m = 0;
    S.clear();
    memset(tmp, -1, sizeof tmp);
    for(int i=0; i<N; ++i)
    {
        if(pop(i)) continue;
        if(m<sz)
        {
            ++m;
            tmp[T[i].lv] = m;
            S.insert(make_pair(T[i].f, m));
        }
        else return false;
    }
    for(int i=0; i<N; ++i) par[i] = tmp[i];
    return 1;
}

void output()
{
    printf("%d\n", res);
    for(int i=0; i<N; ++i)
        printf("%d\n", par[i]);
}

void solve()
{
    int l=1, r=N-1, mid;
    for(int i=0; i<N; ++i) par[i] = i;
    check(N);
    output();
}

int main()
{
    
    init();
    solve();
    return 0;
}

