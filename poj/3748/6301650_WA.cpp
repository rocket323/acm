#include <stdio.h>
#define ll long long

long long n;
int  x, y, A[50];
char str[100];

int main()
{
	scanf("%s", str);
	int p = 0;
	n = x = y = 0;
	while(str[p] != ',')
	{
		if(str[p] >= '0' && str[p] <= '9')
		{
			n = (ll)n * 16 + str[p] - '0';
		}
		else if(str[p] >= 'a' && str[p] <= 'z') n = (ll)n * 16 + str[p] - 'a' + 10;
		else n = (ll)n * 16 + str[p] - 'A' + 10;
		p++;
	}
	p++;
	while(str[p] != ',')
	{
		x = x * 10 + str[p] - '0';
		p++;
	}
	p++;
	while(str[p])
	{
		y = y * 10 + str[p] - '0';
		p++;
	}

	n ^= (n & (1<<x));
	n ^= (n & (7 << (y-2)));
	n |= (6 << (y-2));

	int top = 0;
	while(n)
	{
		A[top++] = n % 16;
		n /= 16;
	}
	for(int i=top-1; i>=0; --i)
		if(A[i] >= 10) printf("%c", 'a' + A[i] - 10);
		else printf("%d", A[i]);
	puts("");
	
	return 0;
}

