#include <stdio.h>
#include <cstring>
#define MaxL 100010
#define Size ((1<<18)-1)

struct Edge
{
	char s[100];
	Edge *next;
}
adj[Size + 10], memo[MaxL];

int n, m, mset;
char S[MaxL];
char *tmp = new char[MaxL];

// BKDR Hash Function
unsigned int hash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
   
    while(*str)
    {
        hash = hash * seed + (*str++);
    }
	return (hash & 0x7FFFFFFF);
}

bool find(int id, char s[])
{
	int tmp = id % Size;
	for(Edge *ptr=adj[tmp].next; ptr; ptr=ptr->next)
		if(strcmp(ptr->s, s)==0) return 1;
	return 0;
}

void add(int id, char s[])
{
	Edge *ptr = &memo[mset++];
	int tmp = id % Size;
	strcpy(ptr->s, s);
	ptr->next = adj[tmp].next;
	adj[tmp].next = ptr;
}

void solve()
{
	scanf("%s", S);
	int len = strlen(S), cnt = 0;

	strcpy(tmp, "");

	mset = 0;
	for(int i=0; i<Size; ++i) adj[i].next = NULL;
	
	for(int i=0; i<n-1; ++i) tmp[i] = S[i];

	for(int i=n-1; i<len; ++i)
	{
		tmp[n-1] = S[i];
		tmp[n] = 0;
		int id = hash(tmp);
		if(!find(id, tmp))
		{
			add(id, tmp);
			cnt++;
		}
		tmp++;
	}

	printf("%d\n", cnt);
}

int main()
{
	while(scanf("%d%d", &n, &m) != EOF)
	{
		solve();
	}
	return 0;
}

