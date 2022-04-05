#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

struct pat
{
	char s[28];
	int idx;
}E[100010];

struct node
{
	int idx, flag;
	node *next[28];
};

node *root, memo[610000];

int n, m, mset;
int p[100010];
char T[100010][9], S[110][30];
bool vis[100010];
int A[100010], top;

bool cmp(pat A, pat B){ return strcmp(A.s, B.s) < 0; }

node * newNode()
{
	node * ptr = &memo[mset++];
	ptr->idx  = ptr->flag = -1;
	for(int i=0; i<28; ++i) ptr->next[i] = NULL;
	return ptr;
}

int getID(char ch)
{
	if(ch >= 'a' && ch <= 'z') return ch - 'a';
	else if(ch == '?') return 26;
	else return 27;
}

void addWord(char str[], int idx)
{
	node * now = root;
	for(int i=0; str[i]; ++i)
	{
		int p = getID(str[i]);
		if(now->next[p] == NULL) now->next[p] = newNode();
		now = now->next[p];
		now->flag = p;
	}
	now->idx = idx;
}

int find(int now)
{
	if(p[now]==now) return now;
	else return p[now] = find(p[now]);
}

void init()
{
	scanf("%d%d", &n, &m);

	mset = 0;

	root = newNode();
	for(int i=0; i<n; ++i)
	{
		scanf("%s", E[i].s);
		E[i].idx = i;
		p[i] = i;
	}

	sort(E, E+n, cmp);

	for(int i=0; i<n; ++i)
	{
		if(i==0 || strcmp(E[i].s, E[i-1].s) != 0) addWord(E[i].s, E[i].idx);
		else p[E[i].idx] = find(E[i-1].idx);
	}
	
	for(int i=0; i<m; ++i) scanf("%s", S[i]);
}

void dfs(int t, int pt, node * now, int len)
{

	if(now == NULL) return;

	/*
			if(now->flag >0 && now->flag<26) printf("%c\n", now->flag+'a');
			else if(now->flag==26) puts("?");
			else puts("*");
*/

	if(pt==len)
	{
		node *tmp = now;
		while(tmp)
		{
			if(tmp->idx != -1) vis[tmp->idx] = 1;
			tmp = tmp->next[27];
		}
	}
	
	if(pt > len) return;

	if(pt < len) dfs(t, pt+1, now->next[S[t][pt] - 'a'], len);

	if(pt < len) dfs(t, pt+1, now->next[getID('?')], len);

	if(pt < len) dfs(t, pt+1, now->next[getID('*')], len);

	if(now->flag == 27)
	{
		if(pt < len) dfs(t, pt+1, now, len);
		
		dfs(t, pt, now->next[S[t][pt-1] - 'a'], len);

		dfs(t, pt, now->next[getID('?')], len);

		dfs(t, pt, now->next[getID('*')], len);

	}
}

void out(int A[])
{
	if(top == 0) puts("Not match");
	else
	{
		for(int i=0; i<top-1; ++i) printf("%d ", A[i]);
		printf("%d\n", A[top-1]);
	}
}

void go(node * now)
{
	for(int i=0; i<28; ++i)
	{
		if(now->next[i])
		{
			if(i<26) printf("%c\n", i+'a');
			else if(i==26) puts("?");
			else puts("*");
			go(now->next[i]);
		}
	}
}

void solve()
{

	//go(root);

	for(int i=0; i<m; ++i)
	{
		for(int j=0; j<n; ++j) vis[j] = 0;
		dfs(i, 0, root, strlen(S[i]));
		top = 0;
		for(int j=0; j<n; ++j)
		{
			vis[j] = vis[find(j)];
			if(vis[j]) A[top++] = j;
		}
		out(A);
	}
}

int main()
{
	init();
	solve();
	if(scanf("%d", &n) != EOF) while(1);
	return 0;
}

