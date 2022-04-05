#include <stdio.h>
#include <cstring>
#define maxl 70

int n, a[maxl], sum, maxlen, pos[maxl], r[maxl], l[maxl], mset, head;

void init()
{
	maxlen = -1;
	sum = 0;

	mset = 0;
	head = mset++;
	l[head] = r[head] = head;

	for(int i=0; i<n; ++i)
	{
		scanf("%d", &a[i]);
		sum += a[i];
		if(a[i] > maxlen) maxlen = a[i];

		pos[mset] = i;
		l[mset] = l[head];
		r[mset] = head;
		l[r[mset]] = r[l[mset]] = mset;

		mset++;
	}
}

bool check(int now, int len, int left)
{
	if(l[head] == head)
	{
		return (left == 0);
	}
	else
	{
		if(left == 0) return check(now + 1, len, len);
		else
		{
			for(int i=r[head]; i!=head; i=r[i])
			{
				int k = pos[i];
				if(a[k] > left) continue;

				l[r[i]] = l[i];
				r[l[i]] = r[i];
				bool flag = check(now, len, left - a[k]);
				l[r[i]] = r[l[i]] = i;

				if(flag) return true;
			}
			return false;
		}
	}
}

void solve()
{
	for(int i=maxlen; i<=sum; ++i)
	{
		if(check(0, i, i))
		{
			printf("%d\n", i);
			return;
		}
	}
}

int main()
{
	while(scanf("%d", &n), n)
	{
		init();
		solve();
	}
	return 0;
}

