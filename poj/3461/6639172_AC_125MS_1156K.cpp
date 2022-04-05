#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

char S[1000011], T[10010];

void solve()
{
	int n = strlen(S);
	int m = strlen(T);

	unsigned int target = 0, num = 0;
	for(int i=0; i<m; ++i)
	{
		target = (target << 1) + T[i];
		num = (num << 1) + S[i];
	}

	unsigned d = 1;
	for(int i=1; i<m; ++i) d <<= 1;

	int ans = 0;
	for(int i=0; i<=n-m; ++i)
	{
		if(num == target && memcmp(S + i, T, min(m, 4)) == 0) ans++;
		num = ((num - S[i] * d) << 1) + S[i + m];
	}
	printf("%d\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%s%s", T, S);
		solve();
	}
	return 0;
}

