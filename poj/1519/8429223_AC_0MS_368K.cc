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
	char str[1000];
	while(scanf("%s", str) != EOF) {
		if(strlen(str) == 1 && str[0] == '0') break;
		n = 0;
		for(int i=0; str[i]; ++i) n += str[i] - '0';
		while(n > 9) n = sum(n);
		printf("%d\n", n);
	}
	return 0;
}
