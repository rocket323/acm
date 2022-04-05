/*
	排序，建图，dfs
*/


#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define MaxL 100010

struct node
{
	int a, b, lv;
}
E[MaxL];

int n, lst;
int mark[MaxL];
int adj[MaxL][4], sz[MaxL], cnt;
int d[MaxL][4];
long long len = 0;

void init()
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i)
	{
		scanf("%d%d", &E[i].a, &E[i].b);
		E[i].lv = i;
	}
	memset(sz, 0, sizeof sz);
	len = cnt = 0;
}

bool cmp1(node A, node B)
{
	return (A.a<B.a ||(A.a==B.a && A.b<B.b));
}

bool cmp2(node A, node B)
{
	return (A.b<B.b ||(A.b==B.b && A.a<B.a));
}

void addEdge(int a, int b, int c)
{
	adj[a][sz[a]] = b;
	d[a][sz[a]] = c;
	sz[a]++;
}

void dfs(int now)
{
	mark[now] = 1;
	cnt++;
	lst = now;
	for(int i=0; i<sz[now]; ++i)
	{
		int k = adj[now][i];
		if(!mark[k])
		{
			len += d[now][i];
			dfs(k);
		}
	}
}

void solve()
{
	
	sort(E, E+n, cmp1);
	for(int i=0; i<n; i+=2)
	{
		if(i+1<n && E[i+1].a==E[i].a)
		{
			addEdge(E[i].lv, E[i+1].lv, E[i+1].b-E[i].b);
			addEdge(E[i+1].lv, E[i].lv, E[i+1].b-E[i].b);
		}
	}
	sort(E, E+n, cmp2);
	for(int i=0; i<n; i+=2)
	{
		if(i+1<n && E[i+1].b==E[i].b)
		{
			addEdge(E[i].lv, E[i+1].lv, E[i+1].a-E[i].a);
			addEdge(E[i+1].lv, E[i].lv, E[i+1].a-E[i].a);
		}
	}
/*	
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<sz[i]; ++j) printf("%d ", adj[i][j]);
		puts("");
	}
*/	
	memset(mark, 0, sizeof mark);
	cnt = 0;
	dfs(0);
	
	bool flag = 0;
	int i;
	for(i=0; i<sz[lst]; ++i)
	{
		if(adj[lst][i]==0){ flag = 1; break; }
	}
	if(flag==0) cnt--;
	else len += d[lst][i];
	
	if(cnt < n) printf("-1\n");
	else cout<<len<<endl;
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