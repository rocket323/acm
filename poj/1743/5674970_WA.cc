#include <stdio.h> 
#include <cstring>
#include <algorithm>
using namespace std;
#define MaxL 20010
#define INF 0x7f7f7f7f
#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)

int n, S[MaxL], rank[MaxL], list[MaxL], b[MaxL], height[MaxL];
int head[MaxL], next[MaxL];
int L[MaxL], f[MaxL][16];

void RMQ_ready()
{
	for(int i=0; i<n; ++i) f[i][0] = i;
	for(int j=1; (1<<j)<=n; ++j)
	{
		for(int i=0; i+(1<<j)-1<n; ++i)
		{
			int k = i + (1<<(j-1));
			if(height[f[i][j-1]] < height[f[k][j-1]]) f[i][j] = f[i][j-1];
			else f[i][j] = f[k][j-1];
		}
	}
}

bool cmp(int i, int j)
{
	return S[i] < S[j];
}

void init()
{
	for(int i=0; i<n; ++i) scanf("%d", &S[i]);
	for(int i=0; i<n-1; ++i) S[i] = S[i+1] - S[i];
	S[n-1] = -INF;

	for(int i=0; i<n; ++i) list[i] = i;
	sort(list, list+n, cmp);
/*
	for(int i=0; i<n; ++i)
	{
		for(int j=list[i]; j<n; ++j) printf("%d ", S[j]);
		puts("");
	}
*/
	b[list[0]] = 0;
	for(int i=1; i<n; ++i)
	{
		if(S[list[i]] == S[list[i-1]]) b[list[i]] = b[list[i-1]];
		else b[list[i]] = i;
	}

	for(int i=1; i<n; ++i)
	{
		int j = 0;
		while((1<<j) <= i) j++;
		--j;
		L[i] = j;
	}
	
}

void suffix_sort()
{
	int i, j, k;
	for(int h=1; h<n; h<<=1)
	{
		for(i=0; i<n; ++i) head[i] = next[i] = -1;
		for(i=n-1; i>=0; --i)
		{
			if(list[i])
			{
				j = list[i] - h; if(j<0) j += n;
				next[j] = head[b[j]]; head[b[j]] = j;
			}
		}
		j = n - h; next[j] = head[b[j]]; head[b[j]] = j;

		for(i=k=0; i<n; ++i)
		{
			if(head[i] >= 0)
			{
				for(j=head[i]; j>=0; j=next[j]) list[k++] = j;
			}
		}
		for(i=0; i<n; ++i)
		{
			if(i>0 && list[i]+h<n && list[i-1]+h<n && b[list[i]]==b[list[i-1]] && b[list[i]+h]==b[list[i-1]+h])
				rank[list[i]] = rank[list[i-1]];
			else rank[list[i]] = i;
		}
		for(i=0; i<n; ++i) b[i] = rank[i];
	}
/*
	for(int i=0; i<n; ++i)
	{
		printf("%d ", i);
		for(int j=list[i]; j<n; ++j) printf("%d ", S[j]);
		puts("");
	}
*/
}

void getHeight()
{
	int i, j, h;
	height[0] = 0;
	for(i=0; i<n; ++i) rank[list[i]] = i;
	for(h=0, i=0; i<n; ++i)
	{
		if(rank[i]>0)
		{
			j = list[rank[i] - 1];
			while(S[i+h]==S[j+h]) ++h;
			height[rank[i]] = h;
			if(h > 0) --h;
		}
	}
/*
	for(int i=0; i<n; ++i)
	{
		printf("h %d %d\n", i, height[i]);
	}
*/
}

int LCP(int i, int j)
{
	int log = L[j - i + 1];
	int k = j - (1<<log) + 1;
	return min(height[f[i][log]], height[f[k][log]]);
}

bool solve(int K)
{
	int head = 0, tail = 0, low = INF, up = -INF;

	low = up = list[head];

	if(K==0) return 1;

	while(tail < n-1)
	{
		tail++;
		int lcp = LCP(head+1, tail);

		if(lcp >= K)
		{
			low = min(low, list[tail]);
			up = max(up, list[tail]);
			if(up - low > K) return true;
		}
		else
		{
			low = up = list[tail];
			head = tail;
		}
	}

	return 0;
}

int main()
{
	while(scanf("%d", &n) && n)
	{
		init();

		suffix_sort();
		RMQ_ready();
		getHeight();


		int l = 0, r = n, ans = 0, mid;
		while(l <= r)
		{
			mid = (l + r) / 2;
			if(solve(mid))
			{
				ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		ans++;
		if(ans < 5) printf("%d\n", 0);
		else printf("%d\n", ans);
	}
	return 0;
}

