#include <stdio.h>
#include <cstring>
#define MaxL 1010
#define INF 0x3f3f3f3f
#define min(a,b) ((a<b)?a:b)

struct node
{
	int lv, flag;
	node *next[4], *fail;
};

node *root, *Q[MaxL], memo[MaxL];

char str[MaxL], s[MaxL], tt[4] = { 'A', 'T', 'C', 'G' };
int f[MaxL][MaxL], n, m, mset, head, tail;

node * newNode()
{
	node *tmp = &memo[mset++];
	for(int i=0; i<4; ++i) tmp->next[i] = NULL;
	tmp->fail = NULL; tmp->flag = 0;
	tmp->lv = mset - 1;
	return tmp;
}

int getID(char ch)
{
	if(ch=='A') return 0;
	if(ch=='T') return 1;
	if(ch=='C') return 2;
	if(ch=='G') return 3;
}

void addWord(node *root, char s[])
{
	node *now = root;
	for(int i=0; s[i]; ++i)
	{
		int p = getID(s[i]);
		if(now->next[p]==NULL) now->next[p] = newNode();
		now = now->next[p];
	}
	now->flag = 1;
}

void AC()
{
	tail = 1;
	Q[head = 0] = root;
	while(head < tail)
	{
		node *now = Q[head++];
		for(int i=0; i<4; ++i)
		{
			if(now->next[i] == NULL) continue;

			node *p = now->fail;
			while(p!=NULL && p->next[i]==NULL) p = p->fail;

			if(p==NULL) now->next[i]->fail = root;
			else now->next[i]->fail = p->next[i];

			now->next[i]->flag |= now->next[i]->fail->flag;

			Q[tail++] = now->next[i];
		}
	}
}

void init()
{
	mset = 0;
	root = newNode();
	for(int i=0; i<m; ++i)
	{
		scanf("%s", s);
		addWord(root, s);
	}
	AC();
}

void solve(int ct)
{
	int ans = INF;

	memset(f, 0x3f, sizeof f);

	scanf("%s", str);
	n = strlen(str);

	f[0][0] = 0;
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<mset; ++j)
		{
			if(f[i][j] >= INF) continue;
			for(int k=0; k<4; ++k)
			{
				node *now = &memo[j];
				while(now!=root && now->next[k]==NULL) now = now->fail;
				now = now->next[k];
				if(now==NULL) now = root;

				int tmp = now->lv;

				if(now->flag) continue;
				f[i+1][tmp] = min(f[i+1][tmp], f[i][j] + (tt[k] != str[i]));
			}
		}
	}

	for(int i=0; i<mset; ++i)
	{
		if(!memo[i].flag) ans = min(ans, f[n][i]);
	}
	printf("Case %d: ", ct);
	if(ans >= INF) printf("-1\n");
	else printf("%d\n", ans);

}

int main()
{
	int ct = 0;
	while(scanf("%d", &m) && m)
	{
		init();
		solve(++ct);
	}
	return 0;
}

