#include <stdio.h>
#include <cstring>
#define maxl 100010

int n, m;
char s[maxl], t[maxl];

int main()
{
	while(scanf("%s%s", s, t) != EOF)
	{
		n = strlen(s);
		m = strlen(t);
		int ans = 0;
		for(int i = 0; i < n; )
		{
			if(n - i < m) break;
			if(strncmp(s + i, t, m) == 0)
			{
				s[i + m - 1] = '#';
				ans++;
				i = i + m;
			}
			else i++;
		}
		printf("%d\n", ans);
	}

	return 0;
}

