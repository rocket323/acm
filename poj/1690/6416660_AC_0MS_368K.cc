#include <stdio.h>
#include <cstring>
#define maxl 300

char str[maxl];
int n, len, opp[maxl], P[maxl], top, no[maxl], tp[maxl];
int cnt[maxl];

void init()
{
	gets(str);
	len = 0;
	for(int i=0; str[i]; ++i) if(str[i] != ' ') str[len++] = str[i];
	str[len] = 0;
}

void solve()
{
	top = 0;
	for(int i=0; i<len; ++i)
	{
		if(str[i] == '(') P[top++] = i;
		else if(str[i] == ')')
		{
			opp[i] = P[--top];
			tp[opp[i]] = i;
		}
	}

	memset(cnt, 0, sizeof cnt);
	for(int i=0; i<len; ++i)
	{
		if(str[i] == '(')
		{
			for(int j=i+1; j<=tp[i]; ++j)
			{
				if(str[j] == '+' || str[j] == '-') cnt[i]++;
			}
		}
	}

	memset(no, 0, sizeof no);
	for(int i=0; i<len; ++i)
	{
		if(str[i] != '(' && str[i] != ')') printf("%c", str[i]);
		else if(str[i] == '(')
		{
			if(i > 0 && str[i - 1] == '-')
			{
				if(cnt[i] == 0) no[i] = 1;
				else printf("%c", str[i]);
			}
			else no[i] = 1;
		}
		else
		{
			if(!no[opp[i]]) printf("%c", str[i]);
		}
	}
	puts("");
}

int main()
{
	int t;
	scanf("%d\n", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}

