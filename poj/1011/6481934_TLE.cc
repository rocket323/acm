#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 70

int n, a[maxl], sum, maxlen, pos[maxl], r[maxl], l[maxl], mset, head;
int v[maxl][maxl], t[maxl];

bool cmp(int a, int b){ return a > b; }

void init()
{
	maxlen = -1;
	sum = 0;

	mset = 0;
	head = mset++;
	l[head] = r[head] = head;

	for(int i=0; i<n; ++i) scanf("%d", &a[i]);
	sort(a, a+n, cmp);

	for(int i=0; i<n; ++i)
	{
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
		
		if(sum < left) return false;

		if(left == 0) return check(now + 1, len, len);
		else
		{
			for(int i=r[head]; i!=head; i=r[i])
			{
				int k = pos[i];
				if(a[k] > left) continue;

				if(now > 0 && left == len && a[k] > v[now-1][0]) continue;
				if(t[now] > 0 && a[k] > v[now][t[now]-1]) continue;

				l[r[i]] = l[i];
				r[l[i]] = r[i];
				sum -= a[k];
				v[now][t[now]++] = a[k];

				bool flag = check(now, len, left - a[k]);

				t[now]--;
				sum += a[k];
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
		memset(t, 0, sizeof t);
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

