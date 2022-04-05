#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;

long long f[60][60];
int n, m;
vector<int> A, cnt;

int main()
{
	int tc = 0;
	while(scanf("%d%d", &n, &m), (n + m))
	{
		printf("Case %d:\n", ++tc);
		A.clear();
		cnt.clear();
		for(int i=0; i<n; ++i)
		{
			int b;
			scanf("%d", &b);
			if(A.size() == 0 || A.back() != b)
			{
				A.push_back(b);
				cnt.push_back(1);
			}
			else cnt[cnt.size() - 1] = cnt[cnt.size() - 1] + 1;
		}

		memset(f, 0, sizeof f);
		f[0][0] = 1;
		for(int i=1; i<=n; ++i)
		{
			f[i][0] = 1;
			for(int j=1; j<n; ++j)
			{
				for(int k=0; k<=cnt[i-1] && k<=j; ++k)
				{
					f[i][j] += f[i-1][j-k];
				}
			}
		}

		for(int i=0; i<m; ++i)
		{
			int b;
			scanf("%d", &b);
			printf("%lld\n", f[n][b]);
		}
	}

	return 0;
}

