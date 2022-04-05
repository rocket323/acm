#include <stdio.h>
#include <cstring>

int main()
{
	int t, a, b, c;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &a, &b, &c);
		int d = b - c;
		if(d > a) puts("advertise");
		else if(d == a) puts("does not matter");
		else puts("do not advertise");
	}
	return 0;
}
