#include <stdio.h>
#include <cstring>
#define MaxL 2010
#define INF 0x3f3f3f3f
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)

struct node
{
	int val, lv;
	node *next[26], *fail;
};

node *root, *Q[MaxL], memo[MaxL * 2];

int len;
int n, m, head, tail, mset, v[MaxL];
char str[110][100];
int f[60][MaxL], g[60][MaxL];
int next_node[60][MaxL], next_char[60][MaxL];

node * newNode()
{
	node *ptr = &memo[mset++];
	ptr->val = 0;
	ptr->lv = mset - 1;
	for(int i=0; i<26; ++i) ptr->next[i] = NULL;
	ptr->fail = NULL;
	return ptr;
}

void addWord(char str[], int idx)
{
	node *now = root;
	for(int i=0; str[i]; ++i)
	{
		int p = str[i] - 'a';
		if(now->next[p] == NULL) now->next[p] = newNode();
		now = now->next[p];
	}
	now->val += v[idx];
}

void AC()
{
	tail = 1;
	Q[head = 0] = root;

	while(head < tail)
	{
		node *now = Q[head++];
		for(int i=0; i<26; ++i)
		{
			if(now->next[i] == NULL) continue;

			node *tmp = now->fail;
			while(tmp != NULL && tmp->next[i] == NULL) tmp = tmp->fail;

			if(tmp == NULL) now->next[i]->fail = root;
			else now->next[i]->fail = tmp->next[i];

			now->next[i]->val += now->next[i]->fail->val;
			Q[tail++] = now->next[i];
		}
	}
}

void init()
{
	mset = 0;
	root = newNode();

	scanf("%d%d", &n, &m);
	for(int i=0; i<m; ++i) scanf("%s", str[i]);
	for(int i=0; i<m; ++i) scanf("%d", &v[i]);

	for(int i=0; i<m; ++i) addWord(str[i], i);

	AC();
}

int dp(int dep, int now)
{
	if(dep > len) return 0;
	if(f[dep][now] != -1) return f[dep][now];

	int ans = 0, ch = INF, pos = -1;
	for(int k=0; k<26; ++k)
	{
		node *tmp = &memo[now];
		while(tmp != root && tmp->next[k] == NULL) tmp = tmp->fail;
		tmp = tmp->next[k] ? tmp->next[k] : root;

		int x = dp(dep + 1, tmp->lv);
		if(x > ans) ans = x, ch = k, pos = tmp->lv;
	}
	f[dep][now] = ans + memo[now].val;
	next_node[dep][now] = pos;
	next_char[dep][now] = ch;

	return f[dep][now];
}

void out(int dep, int now)
{
	if(dep == len) return;
	printf("%c", next_char[dep][now] + 'a');
	out(dep + 1, next_node[dep][now]);
}

void solve()
{
	memset(g, -1, sizeof g);
	g[0][0] = 0;

	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<mset; ++j)
		{
			if(g[i][j] == -1) continue;

			for(int k=0; k<26; ++k)
			{
				node *now = &memo[j];
				while(now != root && now->next[k] == NULL) now = now->fail;
				now = now->next[k] ? now->next[k] : root;

				g[i+1][now->lv] = max(g[i+1][now->lv], g[i][j] + now->val);
			}
		}
	}

	int ans = 0;
	len = 0;
	for(int i=0; i<=n; ++i)
	{
		for(int j=0; j<mset; ++j)
		{
			if(g[i][j] > ans) ans = g[i][j], len = i;
		}
	}
	memset(f, -1, sizeof f);

	dp(0, 0);
	out(0, 0);
	puts("");
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
