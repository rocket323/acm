#include <stdio.h>

int A[10], B[10], c[20], bit, a, b, f[10];

int cnt(int bit, int num, int n, int c[])
{
	int ans = 0;
	for(int i=bit; i>=1; --i)
	{
		int left = 0, right = 0;
		for(int j=bit; j>i; --j) left = left * 10 + c[j];
		if(num != 0) left++;
		for(int j=i-1; j>=1; --j) right = right * 10 + c[j];
		
		if(c[i] > num) ans += left * f[i-1];
		else if(c[i]==num) ans += (left-1) * f[i-1] + right + 1;
		else ans += (left-1) * f[i-1];
	}
	return ans;
}

void fun(int A[], int n)
{
	bit = 0;
	while(n){ c[++bit] = n%10; n /= 10; }
	for(int i=0; i<10; ++i) A[i] = cnt(bit, i, n, c);
}

int main()
{
	f[0] = 1;
	for(int i=1; i<10; ++i) f[i] = f[i-1] * 10;
	while(scanf("%d%d", &a, &b) && (a + b))
	{
		if(a > b){ a^=b; b^=a; a^=b; }
		fun(B, b);
		fun(A, a-1);
		for(int i=0; i<9; ++i) printf("%d ", B[i] - A[i]);
		printf("%d\n", B[9] - A[9]);
	}
	return 0;
}