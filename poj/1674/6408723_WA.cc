
#include <stdio.h>
#include <cstring>
#define ll long long
#define MaxL 100001

ll cnt;
int a[MaxL], c[MaxL], n;

void merge_sort(int s, int t)
{
	if(t-s<=0) return;
	int mid = (s + t) >> 1;
	merge_sort(s, mid);
	merge_sort(mid+1, t);

	int p1 = s, p2 = mid + 1, p = 0;


	ll lst = cnt;
	for(int i=s; i<=t; ++i)
	{
		if((p1 <= mid && a[p1] > a[p2]) || p2 == t+1)
		{
			c[i] = a[p1];
			p1++;
		}
		else
		{
			cnt += (p1 - s);
			c[i] = a[p2];
			p2++;
		}

	}
	for(int i=s; i<=t; ++i) a[i] = c[i];
}

int main()
{
        int t;
        scanf("%d", &t);
	while(t--)
	{
                scanf("%d", &n);
		cnt = 0;
		for(int i=0; i<n; ++i) scanf("%d", &a[i]);
		merge_sort(0, n-1);
		printf("%lld\n", cnt);
	}
	return 0;
}