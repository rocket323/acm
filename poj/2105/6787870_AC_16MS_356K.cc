#include <stdio.h>
#include <cstring>

int main()
{
	int t;
	char str[100];
	scanf("%d", &t);
	while(t--)
	{
		scanf("%s", str);
		for(int i=0; i<4; ++i)
		{
			int ans = 0;
			for(int j=i*8; j<(i+1)*8; ++j) ans = ans * 2 + str[j] - '0';
			printf("%d%c", ans, i == 3 ? '\n' : '.');
		}
	}
	return 0;
}

