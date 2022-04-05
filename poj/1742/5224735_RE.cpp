#include <stdio.h>
#include <cstring>
#define MaxL 100010
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
		for(int d=0; d<A[x]; ++d)
		{
			head = tail = 0;
			for(int j=0; j<=(m/A[x]); ++j)
			{
				if(f[d+j*A[x]] < INF)
				{
					while(head<tail && P[tail-1]>=f[d+j*A[x]]-j) tail--;
					Q[tail] = j;
					P[tail++] = f[d+j*A[x]] - j;
				}
				while(head<tail && Q[head]<j-C[x]) head++;
				if(head<tail) f[d+j*A[x]] = Min(f[d+j*A[x]], P[head] + j);
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
