#include <stdio.h>
#include <cstring>
#include <stdlib.h>

char str[][50] = 
{       
"         _",
"       _/ \\_",
"     _/ \\_/ \\_",
"   _/ \\_/ \\_/ \\_",
" _/ \\_/ \\_/ \\_/ \\_",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/ \\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/ \\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/ \\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/ \\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/ \\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/ \\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/ \\_/ \\_/ \\_/ \\_/",
"  \\_/ \\_/ \\_/ \\_/",
"    \\_/ \\_/ \\_/",
"      \\_/ \\_/",
"        \\_/"
};

char tmp[50][50];

char c[20][20], t[20], s[20];
int n;

int main()
{
	for(int i=0; i<23; ++i)
	{
		for(int j=0; j<50; ++j) printf("%c", str[i][j]);
		puts("");
	}

	while(scanf("%d", &n), n)
	{
		memset(c, 0, sizeof c);
		for(int i=0; i<23; ++i) strcpy(tmp[i], str[i]);
		
		for(int i=0; i<n; ++i)
		{
			scanf("%s%s", t, s);

			int c, r = 0, cnt = 0, cc;

			cc = c = t[0] - 'A';
			for(int j=1; t[j]; ++j)
			{
				r = r * 10 + t[j] - '0';
			}


			cnt = 11 - abs(4 - c);

			c = 2 * c + 1;

			int x = c;
			if(x > 9) x = 18 - x;

			int st = 10 - x - abs(4 - cc);

			r = cnt - r;
			r = st + (r - 1) * 2;

			printf("%s %s : %d %d %c\n", t, s, r, c, tmp[r][c]);
			tmp[r][c] = s[0];
		}

		for(int i=0; i<23; ++i)
		{
			while(tmp[i][strlen(tmp[i]) - 1] == ' ') tmp[i][strlen(tmp[i]) - 1] = 0;
			puts(tmp[i]);
		}
	}
	return 0;
}

