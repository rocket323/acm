#include <stdio.h>
#include <cstring>
#define maxl 1000010

int n;
char s[maxl], t[maxl], ss[maxl];

char Opp(char ch)
{
	switch(ch)
	{
	case 'W': 
		return 'E';
	case 'E':
		return 'W';
	case 'S':
		return 'N';
	case 'N':
		return 'S';
	}
	return 'x';
}

void Process()
{
	for(int i = 0; i < n; ++i)
	{
		ss[i] = Opp(s[n - 1 - i]);
	}

	int h1 = 0, h2 = 0;
	int g1 = 0, g2 = 0;
	for(int i = 0; i < n; ++i)
	{

	}
}

int main()
{
	scanf("%d", &n);
	scanf("%s", s);
	scanf("%s", t);

	Process();

	return 0;
}

