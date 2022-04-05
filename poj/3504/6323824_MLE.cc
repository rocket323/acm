#include <stdio.h>
#include <cstring>

struct node
{
	int cnt;
	node *next[101];
};
node *root, memo[3000000];

int n, f[10100], mset, max_len, tmp[28], l[10010];
char str[10100], word[110];

int max(int a, int b){ return (a>b)?a:b; }

node *newNode()
{
	node *ptr = &memo[mset++];
	ptr->cnt = 0;
	for(int i=0; i<101; ++i) ptr->next[i] = NULL;
	return ptr;
}

void addWord(int str[])
{
	node *now = root;
	for(int i=0; i<=27; ++i)
	{
		int p = str[i];
		if(now->next[p] == NULL) now->next[p] = newNode();
		now = now->next[p];
	}
	now->cnt++;
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
		scanf("%s", word);
		l[i] = strlen(word);
		max_len = max(max_len, l[i]);
		memset(tmp, 0, sizeof tmp);

		tmp[0] = word[0] - 'a';
		
		for(int j=1; j<l[i]-1; ++j) tmp[word[j]-'a'+1]++;

		if(l[i] > 1) tmp[27] = word[l[i]-1] - 'a';
		else tmp[27] = 26;

		addWord(tmp);
	}
}

void solve()
{
	memset(f, 0, sizeof f);
	f[0] = 1;

	int n = strlen(str) - 1;

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
			}
		}
	}

	if(f[n] == 1) puts("this sentence makes perfect sense");
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

