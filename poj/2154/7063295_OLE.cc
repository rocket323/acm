#include <stdio.h>
#include <cstring>

int n, m;

int phi(int n)
{
	 int ans = n;
	 for(int i=2; i<=n/i; ++i)
	 {
		  if(n % i == 0) ans = ans / i * (i - 1);
		  while(n % i == 0) n /= i;
	 }
	 if(n > 1) ans = ans / n * (n - 1);
	 return ans;
}

int pow(int a, int n)
{
	 int ans = 1, t = a % m;
	 while(n)
	 {
		  if(n & 1) ans = (ans * t) % m;
		  t = (t * t) % m;
		  n >>= 1;
	 }
	 return ans;
}

int calc(int len)
{
	 return phi(len) * pow(n, n / len) % m;
}

int main()
{
	 int t;
	 scanf("%d", &t);
	 while(t--)
	 {
		  scanf("%d%d", &n, &m);

		  int ans = 0;
		  for(int i=1; i<=n/i; ++i)
		  {
			   if(n % i) continue;
			   printf("%d %d %d\n", i, calc(i), calc(n/i));
			   ans = (ans + calc(i)) % m;
			   if(n / i != i) ans = (ans + (calc(n / i))) % m;
		  }
		  printf("%d\n", ans);
	 }
	 return 0;
}
