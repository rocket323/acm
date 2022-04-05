#include <stdio.h>
#include <cstring>
#include <algorithm>
#define min(a,b) ((a<b)?a:b)
#define MaxL 200010
using namespace std;

char S[MaxL], T[MaxL];
int n, L[MaxL];
int head[MaxL], next[MaxL], rank1[MaxL], b1[MaxL], L1[MaxL], list1[MaxL], height1[MaxL];
int f1[MaxL][20];

int rank2[MaxL], b2[MaxL], L2[MaxL], list2[MaxL], height2[MaxL];
int f2[MaxL][20];

bool cmp1(int i, int j){ return S[i] < S[j]; }
bool cmp2(int i, int j){ return T[i] < T[j]; }

void suffix_sort(char S[], int list[], int rank[], int b[], bool(* cmp)(int, int))
{
	for(int i=0; i<n; ++i) list[i] = i;
	sort(list, list+n, *cmp);
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

void get_height(char S[], int list[], int rank[], int height[])
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

int rmq_ready(int f[][20], int height[])
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

int LCP(int height[], int f[][20], int i, int j)
{
	if(i > j)
	{
		int tmp = i; i = j; j = tmp;
	}
	int log = L[j - i];
	int k = j - (1<<log) + 1;
	return min(height[f[i+1][log]], height[f[k][log]]);
}


void init()
{
	n = strlen(S);

	for(int i=0; i<n; ++i) T[i] = S[n - 1 - i];

	strcat(S, "$");
	strcat(T, "$");
	n++;

	for(int i=1; i<=n; ++i)
	{
		int j = 0;
		while((1<<j) <= i) j++;
		j--;
		L[i] = j;
	}
}

void solve()
{
	suffix_sort(S, list1, rank1, b1, cmp1);
	get_height(S, list1, rank1, height1);
	rmq_ready(f1, height1);

	suffix_sort(T, list2, rank2, b2, cmp2);
	get_height(T, list2, rank2, height2);
	rmq_ready(f2, height2);

	int period = 1, ans_pos = list1[1], ans_len = 1;

	for(int l=1; l<=n; ++l)
	{
		for(int i=0; i+l<n-1; i+=l)
		{
			int j = i + l;

			if(S[i] != S[j]) continue;

			int right = i + LCP(height1, f1, rank1[i], rank1[j]) - 1;
			int left = i - LCP(height2, f2, rank2[n-2-i], rank2[n-2-j]) + 1;

			int len = right - left + 1 + l;
			int tmp = len / l;

			int low_rank = MaxL, pos = -1;

			for(int k=left; k<=left + len%l; ++k)
			{
				if(rank1[k] < low_rank)
				{
					low_rank = rank1[k];
					pos = k;
				}
			}

			if(tmp > period)
			{
				period = tmp, ans_pos = pos, ans_len = l * tmp;
			}
			else if(tmp == period)
			{
				if(rank1[pos] < rank1[ans_pos])
				{
					ans_pos = pos;
					ans_len = l * period;
				}
			}
		}
	}

	for(int i=ans_pos; i<ans_pos+ans_len; ++i) printf("%c", S[i]);
	puts("");
}

int main()
{
	int tc = 0;
	while(scanf("%s", S) && S[0] != '#')
	{
		printf("Case %d: ", ++tc);
		init();
		solve();
	}
	return 0;
}

