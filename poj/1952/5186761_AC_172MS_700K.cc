#include <stdio.h>
#include <set>
#define INF 0x7f7f7f7f
#define MaxL 5010
using namespace std;

int n, a[MaxL], f[MaxL], cnt[MaxL];
int len;
set<int> S;
set<int>::iterator it;
int Q[MaxL], sz;

int find(int x)
{
	int l = 1, r = sz, ans = -1, mid;
	while(l <= r)
	{
		mid = (l+r) >> 1;
		if(a[Q[mid]] > x)
		{
			ans = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return ans;
}

void Decrease(int a[], int n)
{
	a[n+1] = INF;
	Q[sz = 1] = n + 1;
	f[n+1] = 0;
	for(int i=1; i<=n; ++i)
	{
		int k = find(a[i]);
		f[i] = f[Q[k]] + 1;
		Q[k+1] = i;
		if(k==sz) sz++;
	}
	len = f[Q[sz]];
}

void solve()
{
	int ans = 0;
	
	Decrease(a, n);

	for(int i=1; i<=n; ++i)
	{
		S.clear();
		cnt[i] = 0;
		if(f[i]==1) cnt[i] = 1;
		for(int j=i-1; j>=1; --j)
		{
			if(a[j]<=a[i]) continue;
			it = S.find(a[j]);
			if(f[j]==f[i]-1 && it==S.end()){
				cnt[i] += cnt[j];
				S.insert(a[j]);
			}
		}
	}

	S.clear();
	for(int i=n; i>=1; --i)
	{
		it = S.find(a[i]);
		if(f[i]==len && it==S.end()){ ans += cnt[i]; S.insert(a[i]); }
	}

	printf("%d %d\n", len, ans);
}

int main()
{
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
	solve();
	return 0;
}
