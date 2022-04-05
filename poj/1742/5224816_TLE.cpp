#include <stdio.h>
#include <cstring>
#define MaxL 101010
#define INF 0x3f3f3f3f
#define Min(a,b) ((a<b)?a:b)

int n, m, A[101], C[101], f[MaxL];
int Q[MaxL], head, tail, P[MaxL];

void init()
{
	for(int i=1; i<=n; ++i) scanf("%d", &A[i]);
	for(int i=1; i<=n; ++i) scanf("%d", &C[i]);
}

void solve()
{
	memset(f, 0x3f, sizeof f);

	f[0] = 0;
		
	for(int x=1; x<=n; ++x)
	{
		for(int d=0; d<A[x] && d<=m; ++d)
		{
			head = tail = 0;
			int ed = m / A[x];
			for(int j=0 , i=d; j<=ed && i<=m; ++j, i+=A[x])
			{
				if(f[i] < INF)
				{
					while(head<tail && P[tail-1]>=f[i]-j) tail--;
					Q[tail] = j;
					P[tail++] = f[i] - j;
				}
				while(head<tail && Q[head]<j-C[x]) head++;
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
