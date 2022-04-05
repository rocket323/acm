#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define MaxL 100010

struct node
{
	int dep, idx;
	node *next[26], *fail;
};

node *root, *Q[MaxL], memo[MaxL];

int n, m, w, mset;
char str[1001][1001], s[1001][1001];
int tr[2001], tc[2001], top, len[1001];
int ar[1001], ac[1001], ad[1001];
int head, tail;

node * newNode(int dep)
{
	node * tmp = &memo[mset++];
	for(int i=0; i<26; ++i) tmp->next[i] = NULL;
	tmp->fail = NULL; tmp->idx = -1;
	tmp->dep = dep;
	return tmp;
}

void addWord(node *root, char s[], int idx)
{
	node *now = root;
	for(int i=0; s[i]; ++i)
	{
		int p = s[i] - 'A';
		if(now->next[p] == NULL) now->next[p] = newNode(now->dep + 1);
		now = now->next[p];
	}
	now->idx = idx;
}

void prefix()
{
	tail = 1;
	Q[head = 0] = root;
	while(head < tail)
	{
		node *now = Q[head++];
		for(int i=0; i<26; ++i)
		{
			if(now->next[i] == NULL) continue;

			node *p = now->fail;
			while(p!=NULL && p->next[i]==NULL) p = p->fail;

			if(p==NULL) now->next[i]->fail = root;
			else
			{
				now->next[i]->fail = p->next[i];
			}
			
			Q[tail++] = now->next[i];
		}
	}
}

void go(int key)
{
	node *now = root;
/*
	if(key==7)
	{
		for(int i=0; i<top; ++i) printf("%c", str[tr[i]][tc[i]]);
		puts("");
	}
*/
	for(int i=0; i<top; ++i)
	{
		int p = str[tr[i]][tc[i]] - 'A';

		while(now!=root && now->next[p]==NULL) now = now->fail;
		now = now->next[p];
		if(now==NULL) now = root;

		node *tmp = now;
		while(tmp!=root && tmp->idx!=-1)
		{
			int k = tmp->idx;
			int l = len[k];
			ar[k] = tr[i-l+1], ac[k] = tc[i-l+1], ad[k] = key;
			tmp->idx = -1;
			tmp = tmp->fail;
		}
	}	
}

void swap(int a[], int top)
{
	for(int i=0; i<top/2; ++i)
	{
		int tmp = a[i];
		a[i] = a[top-1-i];
		a[top-1-i] = tmp;
	}
}

void solve()
{
	memset(ar, -1, sizeof ar);
	memset(ac, -1, sizeof ac);
	memset(ad, -1, sizeof ad);
	for(int i=0; i<n; ++i)
	{
		top = 0;
		for(int j=0; j<m; ++j){ tr[top] = i, tc[top++] = j; }
		go(3);
		swap(tr, top), swap(tc, top), go(7);
	}

	for(int i=0; i<m; ++i)
	{
		top = 0;
		for(int j=n-1; j>=0; --j){ tr[top] = j, tc[top++] = i; }
		go(1);
		swap(tr, top), swap(tc, top), go(5);
	}

	for(int i=0; i<n+m-1; ++i)
	{
		top = 0;
		int r = i, c = 0;
		if(r >= n){ r = n - 1; c = i - (n - 1); }
		while(r>=0 && r<n && c>=0 && c<m)
		{
			tr[top] = r, tc[top++] = c;
			r--, c++;
		}
		go(2);
		swap(tr, top), swap(tc, top), go(6);
	}

	for(int i=m-1; i>=m-(n+m-1); --i)
	{
		top = 0;
		int r = 0, c = i;
		if(c < 0) { c = 0, r = -i; }
		while(r>=0 && r<n && c>=0 && c<m)
		{
			tr[top] = r, tc[top++] = c;
			r++, c++;
		}
		go(4);
		swap(tr, top), swap(tc, top), go(8);
	}
	
	for(int i=0; i<w; ++i) printf("%d %d %c\n", ar[i], ac[i], 'A' + ad[i] - 1);
}

void dfs(node *now)
{
	for(int i=0; i<26; ++i)
	{
		if(now->next[i]==NULL) continue;

		printf("%d %c\n", now->next[i]->dep, i+'A');
		dfs(now->next[i]);
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &w);
	for(int i=0; i<n; ++i) scanf("%s", str[i]);

	

	mset = 0;
	root = newNode(0);

	for(int i=0; i<w; ++i)
	{
		scanf("%s", s[i]);
		len[i] = strlen(s[i]);
		addWord(root, s[i], i);
	}


	//dfs(root);

	prefix();

	solve();

	return 0;
}

