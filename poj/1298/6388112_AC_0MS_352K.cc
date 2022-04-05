#include <stdio.h>
#include <cstring>

char str[1000000];

int main()
{
	while(gets(str), str[0] != 'E')
	{
		gets(str);
		for(int i=0; str[i]; ++i)
		{
			if(str[i] >= 'A' && str[i] <= 'Z') printf("%c", (str[i] - 'A' + 21) % 26 + 'A');
			else printf("%c", str[i]);
		}
		puts("");
		gets(str);
	}
}

