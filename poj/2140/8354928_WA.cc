#include <stdio.h>
#include <cstring>
#include <math.h>

int main()
{
	int n;
	while(scanf("%d", &n) != EOF) {
		long long sum = 0;
		int ans = 0;

		for(long long k=1; k*k<=n + 1000; ++k) {
			long long a = (2 * n + k * k - k) / 2 / k;
			if((long long)(2 * a - k + 1) * k == n * (long long)2) {
				if(a >= k) ans++;
				//printf("%i64d %i64d %i64d\n", k, a, (long long)(2 * a - k + 1) * k);
			}
		}

		printf("%d\n", ans);
	}
	return 0;
}
