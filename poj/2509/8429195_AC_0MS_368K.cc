#include <stdio.h>
#include <cstring>

int main()
{
	int n, k;
	while(scanf("%d%d", &n, &k) != EOF) {
		int ans = 0, p = n;
		while(p >= k) {
			ans += p / k * k;
			p = p / k + p % k;
		}
		printf("%d\n", ans + p % k);
	}
	return 0;
}
