#include <stdio.h>
#define MaxL 8000000

int n, q, sz;
int a[MaxL], b[MaxL];

void make(int x1, int y1, int x2, int y2)
{
	if(x1+x2 > n || y1+y2 > n) return;
	make(x1, y1, x1+x2, y1+y2);
	sz++;
	a[sz] = x1+x2;
	b[sz] = y1+y2;
	make(x1+x2, y1+y2, x2, y2);
}

int main()
{
	while(scanf("%d%d", &n, &q) != EOF)
	{
		sz = 1;
		a[1] = 0, b[1] = 1;
		make(0, 1, 1, 1);
		sz++;
		a[sz] = 1, b[sz] = 1;
		for(int i=0; i<q; ++i)
		{
			int k;
			scanf("%d", &k);
			if(k > sz) printf("No Solution\n");
			else printf("%d/%d\n", a[k], b[k]);
		}
	}
	return 0;
}