#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#define INF 0x3f3f3f3f

int a, b, c, d, x, y;

void extend_gcd(int a, int b, int& d, int& x, int& y)
{
	if(b == 0){ d = a; x = 1; y = 0; }
	else
	{
		extend_gcd(b, a % b, d, y, x);
		y -= a / b * x;
	}
}

void calc(int n, int a, int& t1, int& t2)
{
	t1 = n / a;
	if(n < 0 && n % a) t1--;
	t2 = t1 + 1;
}

int getxy(int t)
{
	return abs(x + b / d * t) + abs(y - a / d * t);
}

int getaxby(int t)
{
	return a * abs(x + b / d * t) + b * abs(y - a / d * t);
}

int main()
{
	while(scanf("%d%d%d", &a, &b, &c), (a + b + c))
	{
		extend_gcd(a, b, d, x, y);

		x *= c / d; y *= c / d;

		int t[4], ans = -1;
		calc(-x, b / d, t[0], t[1]);
		calc(y, a / d, t[2], t[3]);

		//printf("%d %d %d %d %d %d\n", x, y, t[0], t[1], t[2], t[3]);

		for(int i=0; i<4; ++i)
		{
			if(ans == INF) ans = t[i];
			else
			{
				if(getxy(t[i]) < getxy(ans)) ans = t[i];
				else if(getxy(t[i]) == getxy(ans) && getaxby(t[i]) < getaxby(ans)) ans = t[i];
			}
		}

		printf("%d %d\n", abs(x + b / d * ans), abs(y - a / d * ans));
	}

	return 0;
}

