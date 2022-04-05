#include <stdio.h>
#include <set>
#define MaxL 5001
using namespace std;

int n, a[MaxL], f[MaxL], cnt[MaxL];
int len;
set<int> S;
set<int>::iterator it;

void solve()
{
	int ans = 0;
	len = 1;
	f[1] = 1;
	for(int i=2; i<=n; ++i)
	{
		f[i] = 1;
		for(int j=1; j<i; ++j)
			if(a[j]>a[i] && f[j]+1>f[i]) f[i] = f[j] + 1;
		if(f[i] > len) len = f[i];
	}

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
