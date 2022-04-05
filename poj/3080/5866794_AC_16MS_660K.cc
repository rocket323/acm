#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define min(a,b) ((a<b)?a:b)
#define MaxL 800

char S[MaxL], T[MaxL];
int p[MaxL], n, num, cnt[MaxL];

int head[MaxL], next[MaxL], rank[MaxL], b[MaxL], L[MaxL], list[MaxL], height[MaxL];
int f[MaxL][20];

bool cmp(int i, int j){ return S[i] < S[j]; }

void suffix_sort()
{
	for(int i=0; i<n; ++i) list[i] = i;
	sort(list, list+n, cmp);
	b[list[0]] = 0;
	for(int i=1; i<n; ++i)
	{
		if(S[list[i]]==S[list[i-1]]) b[list[i]] = b[list[i-1]];
		else b[list[i]] = i;
	}

	int j;
	for(int h=1; h<n; h<<=1)
	{
		for(int i=0; i<n; ++i) head[i] = next[i] = -1;
		for(int i=n-1; i>=0; --i)
		{
			if(list[i])
			{
				j = list[i] - h; if(j < 0)  j += n;
				next[j] = head[b[j]]; head[b[j]] = j;
			}
		}
		j = n - h; next[j] = head[b[j]]; head[b[j]] = j;
		for(int i=0, k=0; i<n; ++i)
		{
			if(head[i] >= 0) for(j=head[i]; j>=0; j=next[j]) list[k++] = j;
		}
		for(int i=0; i<n; ++i)
		{
			if(i>0 && list[i]+h<n && list[i-1]+h<n && b[list[i]]==b[list[i-1]] && b[list[i]+h]==b[list[i-1]+h])
				rank[list[i]] = rank[list[i-1]];
			else rank[list[i]] = i;
		}
		for(int i=0; i<n; ++i) b[i] = rank[i];
	}
}

void get_height()
{
	height[0] = 0;
	for(int i=0; i<n; ++i) rank[list[i]] = i;
	for(int h=0, i=0; i<n; ++i)
	{
		if(rank[i] > 0)
		{
			int j = list[rank[i] - 1];
			while(S[i+h]==S[j+h] && S[i+h]!='$') ++h;
			height[rank[i]] = h;
			if(h > 0) --h;
		}
	}
}

int rmq_ready()
{
	for(int i=0; i<n; ++i) f[i][0] = i;
	for(int j=1; (1<<j)<=n; ++j)
	{
		for(int i=0; (i+(1<<j)-1)<n; ++i)
		{
			int k = i + (1<<(j-1));
			if(height[f[i][j-1]] < height[f[k][j-1]])
				f[i][j] = f[i][j-1];
			else f[i][j] = f[k][j-1];
		}
	}
}

int LCP(int i, int j)
{
	if(i==j) return n -1 - list[i];
	int log = L[j - i];
	int k = j - (1<<log) + 1;
	return min(height[f[i+1][log]], height[f[k][log]]);
}

void init()
{
	scanf("%d", &num);
	strcpy(S, "");
	n = 0;
	memset(p, -1, sizeof p);
	for(int i=1; i<=num; ++i)
	{
		scanf("%s", T);
		
		int len = strlen(T);
		for(int j=n; j<n+len; ++j) p[j] = i;
		
		strcat(S, T);
		strcat(S, "$");

		n += len + 1;
	}
	for(int i=1; i<=n; ++i)
	{
		int j = 0;
		while((1<<j) <= i) ++j;
		j--;
		L[i] = j;
	}
}

void solve()
{
	suffix_sort();
	get_height();
	rmq_ready();

	int head = 0, tail = 0, maxLen = 0, pos = -1, brd = 0;

	memset(cnt, 0, sizeof cnt);
	while(tail < n)
	{
		while(tail < n)
		{
			tail++;
			if(tail == n) break;
			if(S[list[tail]] != '$')
			{
				cnt[p[list[tail]]]++;
				if(cnt[p[list[tail]]] == 1) brd++;
			}
			if(brd == num)
			{
				int lcp = LCP(head, tail);
				if(lcp > maxLen)
				{
					maxLen = lcp;
					pos = list[head];
				}
				break;
			}
		}

		if(tail == n) break;
		while(head < tail)
		{
			if(S[list[head]] != '$')
			{
				cnt[p[list[head]]]--;
				if(cnt[p[list[head]]] == 0) brd--;
			}
			head++;
			if(brd == num)
			{
				int lcp = LCP(head, tail);
				if(lcp > maxLen)
				{
					maxLen = lcp;
					pos = list[head];
				}
			}
			else break;
		}
	}
	if(maxLen < 3) puts("no significant commonalities");
	else
	{
		for(int i=pos; i<pos+maxLen; ++i) printf("%c", S[i]);
		puts("");
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}

