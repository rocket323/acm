#include <stdio.h>
#include <cstring>

struct node
{
	int cnt;
	node *next[2];
};
node *root, memo[3000000];

char mp[26][10] = 
{
	".-", "-...", "-.-.", "-..",
	".", "..-.", "--.", "....",
	"..", ".---", "-.-", ".-..",
	"--", "-.", "---", ".--.",
	"--.-", ".-.", "...", "-",
	"..-", "...-", ".--", "-..-",
	"-.--", "--.."
};

int n, f[10100], mset;
char str[10100], word[10100][30];

int getID(char ch)
{
	return (ch == '.') ? 0 : 1;
}

node *newNode()
{
	node *ptr = &memo[mset++];
	ptr->cnt = 0;
	for(int i=0; i<2; ++i) ptr->next[i] = NULL;
	return ptr;
}

void addWord(char str[])
{
	node *now = root;
	for(int i=0; str[i]; ++i)
	{
		for(int j=0; j<mp[str[i]-'A'][j]; ++j)
		{
			int p = getID(mp[str[i]-'A'][j]);
			if(now->next[p] == NULL) now->next[p] = newNode();
			now = now->next[p];
		}
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
	for(int i=0; i<n; ++i)
	{
		scanf("%s", word[i]);
		addWord(word[i]);
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
		int pos = i+1;
		while(pos <= n && now->next[getID(str[pos])])
		{
			now = now->next[getID(str[pos])];
			f[pos] += f[i] * now->cnt;
			pos++;
		}
	}
	printf("%d\n", f[n]);
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

