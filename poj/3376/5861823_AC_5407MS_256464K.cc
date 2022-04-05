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
	//for(int i=1; i<=n; ++i) printf("n %d %d\n", s[i], t[i]);
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
/*
	for(int i=0; i<n; ++i) printf("%c", S[i]);
	puts("");

	for(int i=0; i<n; ++i) printf("%d ", lcp[i]);
	puts("");
*/
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
		//printf("%c ", S[i]);
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

void check(node *now)
{
	printf("%d %d\n", now->cnt, now->finish);

	for(int i=0; i<26; ++i)
	{
		if(now->next[i]){ printf("%c\n", i+'a'); check(now->next[i]); }
	}
}

void solve()
{
	mset = 0;
	root = newNode();

	//for(int i=1; i<=n; ++i) printf("%d %d\n", s[i], t[i]);
	//puts("");

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

		//printf("%d %d\n", s[i], t[i]);

		//for(int j=0; j<len; ++j) printf("%c", B[j]);
		//puts("");

		addWord(i, B, len);
	}
/*
	for(int i=1; i<=n; ++i)
	{
		for(int j=0; j<(t[i]-s[i]+1); ++j) printf("%d ", prefix[j+s[i]]);
		puts("");
	}
*/
	//check(root);

	ans = 0;
	for(int i=1; i<=n; ++i) go(i, t[i] - s[i] + 1);

	printf("%I64d\n", ans);
}

int main()
{
	scanf("%d", &n);
	init();
	solve();
	return 0;
}
