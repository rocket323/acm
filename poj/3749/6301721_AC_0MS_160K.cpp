#include <stdio.h>
#include <cstring>

char str[1000];

int main()
{
	while(gets(str))
	{
		if(strcmp(str, "ENDOFINPUT") == 0) break;
		gets(str);

		for(int i=0; str[i]; ++i)
		{
			if(str[i] >= 'A' && str[i] <= 'Z')
			{
				int k = str[i] - 'A';
				k = (k - 5 + 26) % 26;
				printf("%c", 'A' + k);
			}
			else printf("%c", str[i]);
		}
		puts("");

		gets(str);
	}
}
