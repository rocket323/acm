#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

struct word
{
	char s[26];
	int idx;
}E[110];

struct node
{
	int idx, last;
	node *next[26];
};

node *root, memo[10000];

int n, m, flag, mset;
int p[110];
char T[100010][9], S[110][30];
vector<int> A[110];

bool cmp(word A, word B){ return strcmp(A.s, B.s) < 0; }
bool cmp2(word A, word B){ return A.idx < B.idx; }

node * newNode()
{
	node * ptr = &memo[mset++];
	ptr->idx  = ptr->last = -1;
	for(int i=0; i<26; ++i) ptr->next[i] = NULL;
	return ptr;
}

void addWord(char str[], int idx)
{
	node * now = root;
	for(int i=0; str[i]; ++i)
	{
		int p = str[i] - 'a';
		if(now->next[p] == NULL) now->next[p] = newNode();
		now = now->next[p];
	}
	now->idx = idx;
}

void init()
{
	scanf("%d%d", &n, &m);

	mset = 0;
	for(int i=0; i<n; ++i) scanf("%s", T[i]);
	for(int i=0; i<m; ++i)
	{
		scanf("%s", E[i].s);
		E[i].idx = i;
	}

	root = newNode();
	sort(E, E+m, cmp);
	for(int i=0; i<m; ++i)
	{
		if(i==0 || strcmp(E[i].s, E[i-1].s) != 0)
		{
			addWord(E[i].s, E[i].idx);
			p[E[i].idx] = E[i].idx;
		}
		else p[E[i].idx] = p[E[i-1].idx];
	}
}

void dfs(int t, int pt, node * now, int len)
{

	if(now == NULL) return;

	if(now->idx != -1 && pt==len)
	{
		if(now->last != t) A[now->idx].push_back(t), now->last = t;
	}

	if(pt == len) return;

	if(T[t][pt] == '*')
	{
		dfs(t, pt+1, now, len);
		if(flag) return;
		for(int i=0; i<26; ++i) dfs(t, pt, now->next[i], len);
	}
	else if(T[t][pt] == '?')
	{
		for(int i=0; i<26; ++i) dfs(t, pt+1, now->next[i], len);
	}
	else
	{
		for(int i=0; i<26; ++i) dfs(t, pt+1, now->next[T[t][pt] - 'a'], len);
	}
}

void out(int idx)
{
	int size = A[idx].size();
	if(size == 0) puts("Not match");
	else
	{
		for(int i=0; i<size-1; ++i) printf("%d ", A[idx][i]);
		printf("%d\n", A[idx][size-1]);
	}
}

void go(node * now)
{
	for(int i=0; i<26; ++i)
	{
		if(now->next[i])
		{
			printf("%c\n", i+'a');
			go(now->next[i]);
		}
	}
}

void solve()
{
	for(int i=0; i<m; ++i) A[i].clear();

	//go(root);

	for(int i=0; i<n; ++i) dfs(i, 0, root, strlen(T[i]));

	sort(E, E+m, cmp2);

	for(int i=0; i<m; ++i)
	{
		out(p[E[i].idx]);
	}
}

int main()
{
	init();
	solve();
	return 0;
}

