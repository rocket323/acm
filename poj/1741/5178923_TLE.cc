#include <stdio.h>

#include <algorithm>

#include <cstring>
#include <set>

#define MaxL 10010

using namespace std;

#define Max(a,b) ((a>b)?a:b)



struct Edge

{

    int idx, len;

    Edge * next;

}adj[MaxL], memo[2*MaxL];



int n, K, ans;

int mset;

char vis[MaxL];

int Q[MaxL], top;

int lv[MaxL], sz;

int Size[MaxL];

int ST[MaxL], head, tail;

int d[MaxL];

int visit[MaxL], vs;
set<int> S;
set<int>::iterator it;



inline void addEdge(int a, int b, int len)

{

    Edge * ptr = &memo[mset++];

    ptr->idx = b;

    ptr->len = len;

    ptr->next = adj[a].next;

    adj[a].next = ptr;

}



void init()

{

    mset = 0;

    for(int i=0; i<=n; ++i) adj[i].next = NULL;

    for(int i=1; i<n; ++i)

    {

        int a, b, c;

        scanf("%d%d%d", &a, &b, &c);

        addEdge(a, b, c);

        addEdge(b, a, c);

    }
    S.clear();
    for(int i=1; i<=n; ++i) S.insert(i);

}



inline int getCount(int l, int r)

{

    //sort(Q+l, Q+r+1);

    int ans = 0;

    while(l < r)

    {

        while(l < r && Q[l]+Q[r]>K) --r;

        if(l < r) ans += (r - l);

        ++l;

    }

    return ans;

}



void add_Q(int now, int len)

{

    

    vis[now] = 1;

    Q[++top] = len;

    for(Edge * ptr=adj[now].next; ptr; ptr=ptr->next)

    {

        if(!vis[ptr->idx]) add_Q(ptr->idx, len + ptr->len);

    }

    vis[now] = 0;



}



int handleSubTree(int now)

{



    int ans = 0;

    top = 0;



    for(Edge * ptr=adj[now].next; ptr; ptr=ptr->next)

    {

        if(!vis[ptr->idx])

        {

            int sl = top + 1;

            add_Q(ptr->idx, ptr->len);

            sort(Q+sl, Q+top+1);

            ans -= getCount(sl, top);

        }

    }



    Q[0] = 0;

    sort(Q, Q+top+1);

    ans += getCount(0, top);

    return ans;

}



void dfs_for_root(int now)

{

    lv[++sz] = now;

    Size[now] = 1;

    vis[now] = 1;

   

    for(Edge * ptr=adj[now].next; ptr; ptr=ptr->next)

    {

        if(!vis[ptr->idx])

        {

            dfs_for_root(ptr->idx);

            Size[now] += Size[ptr->idx];

        }

    }

    vis[now] = 0;

}



int chooseRoot(int now)

{

    sz = 0;

    dfs_for_root(now);



    int Min = MaxL;

    int ans = 0;

    

    for(int i=1; i<=sz; ++i)

    {

        int x = Max(Size[lv[i]]-1, sz - Size[lv[i]]);

        if(x <= Min)

        {

            Min = x;

            ans = lv[i];

        }

    }

    

    return ans;

}



int dfs(int now)

{


    int ans = 0;

    for(int cnt=0; cnt<n; ++cnt)
    {
        it = S.begin();
        int a = *it;
        int root = chooseRoot(a);
        vis[root] = 1;
        ans += handleSubTree(root);
        S.erase(it);
    }
    

    return ans;

}



int solve()

{

    memset(vis, 0, sizeof vis);

    

    ans = dfs(1);

    return ans;

}



int main()

{

    while(scanf("%d%d", &n, &K) && n)

    {

        init();

        printf("%d\n", solve());

    }

    return 0;

}


