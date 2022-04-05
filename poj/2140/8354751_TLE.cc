#include <stdio.h>
#include <cstring>
#include <math.h>

int main()
{
	int n;
	while(scanf("%d", &n) != EOF) {
		long long sum = 0;
		int ans = 0;
		for(int i=1; i<=n; ++i) {
			sum = sum + (long long)i;

			int l = 0, r = i, mid, tmp = -1;
			long long x = sum - n;
			if(x < 0) continue;

			long long p = x * 2;

			long long k = ( -1 + sqrt(1.0 + 4 * p) ) / 2 + 0.5;
			
			if(k * k + k == p) ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
