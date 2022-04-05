#include <stdio.h>
#include <math.h>

int main()
{
	int n, m;
	double pi = acos(-1), e = exp(1.0);
	scanf("%d", &m);
	while(m--) {
		scanf("%d", &n);
		double ans = 0.0;
		if(n <= 100000) 
			for(int i=1; i<=n; ++i) ans += log10(i * 1.0);
		else
			ans = log10(2 * pi * n) + n * log10(n * 1.0 / e);
		printf("%.0lf\n", ans + 0.5);
	}
	return 0;
}
