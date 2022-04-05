#include <stdio.h>
#include <cstring>

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
			while(l <= r) {
				mid = (l + r) / 2;
				if((long long)mid * (mid + 1) / 2 <= x) {
					if((long long)mid * (mid + 1) / 2 == x) tmp = mid;
					l = mid + 1;
				}
				else r = mid - 1;
			}
			
			if(tmp != -1) ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
