#include <stdio.h>
#include <cstring>
#define maxl 100010

int n;
char s[maxl];
int sum[maxl], a[maxl], b[maxl];

bool Process(int a_start, int a_end, int s_start, int s_end, int carry_left, int carry_right)
{
	if(carry_left > 1 || carry_left < 0) return false;
	if(a_start > a_end)
	{
		return carry_left == carry_right;
	}

	int na = -1, nb = -1, num = carry_left * 10 + sum[s_end] - carry_right;
	if(sum[s_end] - carry_right == 9) num = 9;
	if(num < 0) num = 10 - carry_right;
	for(int i = 0; i < 10; ++i)
	{
		if(a_start == 0 && i == 0) continue;

		int tmp = num - i;
		if(a_start == a_end && i != tmp) continue;
		if(tmp >= 0 && tmp < 10)
		{
			na = i;
			nb = tmp;
			break;
		}
	}

	if(na == -1) return false;

	a[a_start] = na;
	a[a_end] = nb;
	if(a_start == a_end) return true;

	int carry_left_now = sum[s_start] + carry_left * 10 - (na + nb);
	return Process(a_start + 1, a_end - 1, s_start + 1, s_end - 1, carry_left_now, (na + nb + carry_right) / 10);
}

int main()
{
	while(scanf("%s", s) != EOF)
	{
		int n = strlen(s);
		for(int i = 0; i < n; ++i) sum[i] = s[i] - '0';

		bool check = Process(0, n - 2, 1, n - 1, sum[0], 0);
		if(check)
		{
			for(int i = 0; i < n - 1; ++i) printf("%d", a[i]);
			puts("");
			continue;
		}

		check = Process(0, n - 1, 0, n - 1, 0, 0);
		if(check)
		{
			for(int i = 0; i < n; ++i) printf("%d", a[i]);
			puts("");
			continue;
		}

		puts("0");
	}

	return 0;
}

