#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll long long
#define MaxL 2000010

struct node
{
	int cnt, finish;
	node * next[26];
};

node *root, memo[MaxL + 100];


char str[MaxL], tmp[MaxL], A[MaxL], B[MaxL];
int s[MaxL], t[MaxL], n, sum, mset;
int prefix[MaxL], suffix[MaxL], next[MaxL], lcp[MaxL];
ll ans;

void init()
{
	sum = 0;
	s[0] = t[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		int l;
		scanf("%d ", &l);
		sum += l;
		s[i] = t[i-1] + 1;
		t[i] = s[i] + l - 1;
		for(int j=s[i]; j<=t[i]; ++j)
		{
			scanf("%c", &str[j]);
		}
		getchar();
	}
}

void next_function(char S[], int n)
{
	int j = 0, k = 1;
	while(1+j<n && S[j] == S[1+j]) j++;
	next[1] = j;

	for(int i=2; i<n; ++i)
	{
		int len = k + next[k] - 1;
		int l = next[i - k];
		if(l < len - i + 1) next[i] = l;
		else
		{
			int j = max(0, len - i + 1);
			while(S[i+j] == S[j] && i + j < n) j++;
			next[i] = j;
			k = i;
		}
	}
}

void extend_kmp(char S[], char T[], int n, int m)
{
	next_function(T, m);

	int j = 0, k = 0;
	while(j<min(n, m) && T[j] == S[j]) ++j;
	lcp[0] = j;
	
	for(int i=1; i<n; ++i)
	{
		int len = k + lcp[k] - 1;
		int l = next[i - k];
		if(l < len - i + 1) lcp[i] = l;
		else
		{
			int j = max(0, len - i + 1);
			while(i+j<n && j<m && S[i+j]==T[j]) j++;
			lcp[i] = j;
			k = i;
		}
	}
}

node *newNode()
{
	node *ptr = &memo[mset++];
	ptr->cnt = 0;
	ptr->finish = 0;
	for(int i=0; i<26; ++i) ptr->next[i] = NULL;
	return ptr;
}

void addWord(int idx, char S[], int len)
{
	node *now = root;
	for(int i=0; i<len; ++i)
	{
		int p = S[i] - 'a';
		if(now->next[p] == NULL) now->next[p] = newNode();
		now = now->next[p];
		if(i < len - 1 && prefix[len-i-2 + s[idx]]) now->cnt++;
	}
	now->finish++;
}

void go(int idx, int len)
{
	node *now = root;

	for(int i=0; i<len; ++i)
	{
		int p = str[i + s[idx]] - 'a';
		now = now->next[p];
		if(now==NULL) return;

		if(i==len-1 || suffix[s[idx] + i + 1]) ans += now->finish;
	}
	ans += now->cnt;
}

void solve()
{
	mset = 0;
	root = newNode();

	int len;
	for(int i=1; i<=n; ++i)
	{
		for(int j=s[i]; j<=t[i]; ++j) A[j-s[i]] = str[j];
		A[len = t[i] - s[i] + 1] = 0;
		for(int j=0; j<len; ++j) B[j] = A[len - 1 - j];
		B[len] = 0;

		extend_kmp(B, A, len, len);
		for(int j=0; j<len; ++j) prefix[j + s[i]] = (lcp[len-1-j] == j + 1);

		extend_kmp(A, B, len, len);
		for(int j=0; j<len; ++j) suffix[j + s[i]] = (lcp[j] == len - j);

		addWord(i, B, len);
	}
	ans = 0;
	for(int i=1; i<=n; ++i) go(i, t[i] - s[i] + 1);

	printf("%lld\n", ans);
}

int main()
{
	scanf("%d", &n);
	init();
	solve();
	return 0;
}
