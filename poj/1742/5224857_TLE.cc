#include <stdio.h>
#include <cstring>
#include <algorithm>
#define MaxL 101010
#define INF 0x3f3f3f3f
using namespace std;
#define Min(a,b) ((a<b)?a:b)

struct node
{
	int a, c;
}
E[101], T[101];

int n, m, f[MaxL];
int Q[MaxL], head, tail, P[MaxL];

bool cmp(node A, node B){ return A.a<B.a; }

void init()
{
	for(int i=1; i<=n; ++i) scanf("%d", &T[i].a);
	for(int i=1; i<=n; ++i) scanf("%d", &T[i].c);
	sort(T+1, T+1+n, cmp);

	int ct = 1;
	E[1].a = T[1].a; E[1].c = T[1].c;

	for(int i=1; i<=n; ++i)
	{
		if(T[i].a==E[ct].a) E[ct].c += T[i].c;
		else
		{
			ct++;
			E[ct].a = T[ct].a;
			E[ct].c = T[ct].c;
		}
	}
	n = ct;
}

void solve()
{
	memset(f, 0x3f, sizeof f);

	f[0] = 0;
		
	for(int x=1; x<=n; ++x)
	{
		for(int d=0; d<E[x].a  && d<=m; ++d)
		{
			head = tail = 0;
			int ed = m / E[x].a;
			for(int j=0 , i=d; j<=ed && i<=m; ++j, i+=E[x].a)
			{
				if(f[i] < INF)
				{
					while(head<tail && P[tail-1]>=f[i]-j) tail--;
					Q[tail] = j;
					P[tail++] = f[i] - j;
				}
				while(head<tail && Q[head]<j-E[x].c) head++;
				if(head<tail) f[i] = Min(f[i], P[head] + j);
			}
		}
	}
	int cnt = 0;
	for(int i=1; i<=m; ++i) if(f[i] < INF) cnt++;
	printf("%d\n", cnt);
}

int main()
{
	while(scanf("%d%d", &n, &m) && (n+m))
	{
		init();
		solve();
	}
	return 0;
}
