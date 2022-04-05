#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define maxl 50010

struct node
{
	int idx;
	node *next[10];
};

node *root, memo[maxl * 50];

int n, len, l[maxl], mp[260], f[200], mset, p[200], w[200];
char S[200], str[maxl][51];

node *newNode()
{
	node *ptr = &memo[mset++];
	ptr->idx = -1;
	for(int i=0; i<10; ++i) ptr->next[i] = NULL;
	return ptr;
}

void addWord(int idx, char str[])
{
	node *now = root;
	for(int i=0; str[i]; ++i)
	{
		int p = mp[str[i]];
		if(now->next[p] == NULL) now->next[p] = newNode();
		now = now->next[p];
	}
	now->idx = idx;
}

void init()
{
	mset = 0;
	root = newNode();

	len =strlen(S);
	scanf("%d", &n);
	for(int i=0; i<n; ++i)
	{
		scanf("%s", str[i]);
		addWord(i, str[i]);
	}
}

void go(node *now)
{
	for(int i=0; i<10; ++i)
	{
		if(now->next[i] != NULL)
		{
			printf("%d\n", i);
			go(now->next[i]);
		}
	}
}

void out(int now)
{
	if(p[now] == 0)
	{
		printf("%s", str[w[now]]);
	}
	else
	{
		out(p[now]);
		printf(" %s", str[w[now]]);
	}
}

void solve()
{

	memset(f, 0x3f, sizeof f);
	memset(p, -1, sizeof p);
	memset(w, -1, sizeof w);
	f[0] = 0;
	for(int i=0; i<len-1; ++i)
	{
		if(f[i] == INF) continue;
		
		int j = i + 1;
		node *now = root;
		while(j < len)
		{
			now = now->next[S[j] - '0'];
			if(now == NULL) break;

			if(now->idx != -1)
			{
				if(f[i] + 1 < f[j])
				{
					f[j] = f[i] + 1;
					p[j] = i;
					w[j] = now->idx;
				}
			}
			j++;
		}
	}

	out(len - 1);
	puts("");
}

int main()
{
	mp['i'] = 1; mp['j'] = 1; mp['a'] = 2; mp['b'] = 2; mp['c'] = 2; mp['d'] = 3; 
	mp['e'] = 3; mp['f'] = 3; mp['g'] = 4; mp['h'] = 4; mp['k'] = 5; mp['l'] = 5; 
	mp['m'] = 6; mp['n'] = 6; mp['p'] = 7; mp['r'] = 7; mp['s'] = 7; mp['t'] = 8; 
	mp['u'] = 8; mp['v'] = 8; mp['w'] = 9; mp['x'] = 9; mp['y'] = 9; mp['o'] = 0; 
	mp['q'] = 0; mp['z'] = 0;
	while(scanf("%s", S + 1) != EOF)
	{
		S[0] = '$';
		init();
		solve();
	}
	return 0;
}

