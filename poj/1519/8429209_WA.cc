#include <stdio.h>
#include <cstring>

int sum(int n) {
	int ans = 0;
	while(n) {
		ans += n % 10;
		n /= 10;
	}
	return ans;
}

int main()
{
	int n;
	while(scanf("%d", &n), n) {
		while(n > 9) n = sum(n);
		printf("%d\n", n);
	}
	return 0;
}
