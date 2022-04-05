#include <stdio.h>
#include <cstring>

struct node
{
	short cnt, flag;
	node *next[101];
};
node *root, memo[120000];

int n, f[1010], mset, max_len, tmp[28], l[10010], pre[1010], idx[1010];
char str[1010], word[10100][110];

int max(int a, int b){ return (a>b)?a:b; }

node *newNode()
{
	node *ptr = &memo[mset++];
	ptr->cnt = 0;
	ptr->flag = -1;
	for(int i=0; i<101; ++i) ptr->next[i] = NULL;
	return ptr;
}

void addWord(int str[], int idx)
{
	node *now = root;
	for(int i=0; i<=27; ++i)
	{
		int p = str[i];
		if(now->next[p] == NULL) now->next[p] = newNode();
		now = now->next[p];
	}
	now->cnt++;
	now->flag = idx;
}

void init()
{

	mset = 0;
	root = newNode();

	scanf("%s", str+1);
	str[0] = 'a';
	scanf("%d", &n);
	max_len = 0;
	for(int i=0; i<n; ++i)
	{
		scanf("%s", word[i]);
		l[i] = strlen(word[i]);
		max_len = max(max_len, l[i]);
		memset(tmp, 0, sizeof tmp);

		tmp[0] = word[i][0] - 'a';
		
		for(int j=1; j<l[i]-1; ++j) tmp[word[i][j]-'a'+1]++;

		if(l[i] > 1) tmp[27] = word[i][l[i]-1] - 'a';
		else tmp[27] = 26;

		addWord(tmp, i);
	}
}

void out(int p)
{
	if(p == 0) return;
	out(pre[p]);
	printf("%s", word[idx[p]]);
}

void solve()
{
	memset(f, 0, sizeof f);
	f[0] = 1;

	int n = strlen(str) - 1;

	memset(pre, -1, sizeof pre);
	for(int i=0; i<n; ++i)
	{
		node *now = root;

		for(int j=i+1; j<=i+max_len && j<=n; ++j)
		{
			memset(tmp, 0, sizeof tmp);
			tmp[0] = str[i+1] - 'a';
			for(int k=i+2; k<j; ++k) tmp[str[k]-'a'+1]++;
			if(j - i > 1) tmp[27] = str[j] - 'a';
			else tmp[27] = 26;

			node *now = root;
			for(int k=0; k<=27; ++k)
			{
				if(now->next[tmp[k]]) now = now->next[tmp[k]];
				else
				{
					now = NULL;
					break;
				}
			}
			if(now)
			{
				f[j] += f[i] * now->cnt;
				pre[j] = i;
				idx[j] = now->flag;
				if(f[j] > 1) f[j] = 2;
			}
		}
	}

	if(f[n] == 1)
	{
		out(n);
		puts("");
	}
	else if(f[n] == 0) puts("impossible");
	else puts("ambiguous");
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

