#include <stdio.h>
#include <cstring>

int n, t, a[200], sum, cnt;

int main()
{
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		sum = 0;
		cnt = 0;
		for(int i=0; i<n; ++i) {
			scanf("%d", &a[i]);
			sum += a[i];
		}
		for(int i=0; i<n; ++i) if(a[i] * n > sum) cnt++;
		printf("%.3lf%%\n", (double)cnt / n * 100);
	}
	return 0;
}
