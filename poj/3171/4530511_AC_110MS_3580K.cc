#include <iostream>
#include <algorithm>
#define MaxN 10010
#define MaxL 90000
#define INF 2000000000
using namespace std;

struct cow{
    int t1, t2, s;
}C[MaxN];

struct node{
    int l, r;
    int w;
}nd[4*MaxL];

int N, S, T;

bool cmp(cow A, cow B){ return A.t2<B.t2; }
int Min(int a, int b){ return (a<b)?a:b; }

void build(int now, int l, int r)
{
    nd[now].l=l; nd[now].r=r;
    nd[now].w=INF;
    if(nd[now].l==nd[now].r&&nd[now].l==S-1)
        nd[now].w = 0;
    if(l<r)
    {
        int mid = (l+r)>>1;
        build(2*now, l, mid);
        build(2*now+1, mid+1, r);
        nd[now].w = Min(nd[2*now].w, nd[2*now+1].w);
    }
}

void init()
{
    scanf("%d%d%d", &N, &S, &T);
    for(int i=0; i<N; ++i)
    {
        scanf("%d%d%d", &C[i].t1, &C[i].t2, &C[i].s);
    }
    sort(C, C+N, cmp);
    build(1, S-1, T);
}

int getTree(int now, int l, int r)
{
    if(l<=nd[now].l&&nd[now].r<=r)
        return nd[now].w;
    int mid = (nd[now].l+nd[now].r)>>1;
    int lv=INF, rv=INF;
    if(l<=mid) lv = getTree(2*now, l, r);
    if(r>mid) rv = getTree(2*now+1, l, r);
    return Min(lv, rv);
}

void change(int now, int l, int r, int num)
{
    if(l<=nd[now].l&&nd[now].r<=r)
    {
        if(nd[now].w>num) nd[now].w=num;
        return;
    }
    int mid = (nd[now].l+nd[now].r)>>1;
    if(l<=mid) change(2*now, l, r, num);
    if(r>mid) change(2*now+1, l, r, num);
    nd[now].w = Min(nd[2*now].w, nd[2*now+1].w);
}

void process()
{
    for(int i=0; i<N; ++i)
    {
        int k = getTree(1, C[i].t1-1, C[i].t2);
        change(1, C[i].t2, C[i].t2, k+C[i].s);
    }
    int ans = getTree(1, C[N-1].t2, C[N-1].t2);
    if(ans>=INF) printf("-1\n");
    else printf("%d\n", ans);
}

int main()
{
    init();
    process();
    return 0;
}
