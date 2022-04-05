#include <stdio.h>
#include <cstring>
#define mod 100000

struct node
{
	int lv, flag;
	node *next[4], *fail;
};

node *root, *Q[1000], memo[1000];

int head, tail;
int A[110][110], B[110][110], I[110][110], tmp[110][110], n, m, mset;
char str[110];

node * newNode()
{
	node * ptr = &memo[mset++];
	ptr->lv = mset - 1;
	ptr->flag = 0;
	ptr->fail = NULL;
	for(int i=0; i<4; ++i) ptr->next[i] = NULL;
	return ptr;
}

int getID(char ch)
{
	if(ch == 'A') return 0;
	if(ch == 'C') return 1;
	if(ch == 'G') return 2;
	if(ch == 'T') return 3;
}

void addWord(char str[])
{
	node * now = root;
	for(int i=0; str[i]; ++i)
	{
		int p = getID(str[i]);
		if(now->next[p] == NULL) now->next[p] = newNode();
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
		node * now = Q[head++];
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
		scanf("%s", str);
		addWord(str);
	}
	AC();
}

void matrix(int c[][110], int a[][110], int b[][110])
{
	for(int i=0; i<mset; ++i) for(int j=0; j<mset; ++j) c[i][j] = 0;

	for(int i=0; i<mset; ++i)
	{
		for(int k=0; k<mset; ++k)
		{
			if(a[i][k] == 0) continue;
			for(int j=0; j<mset; ++j) c[i][j] = (c[i][j] + (long long)a[i][k] * b[k][j]) % mod;
		}
	}
}

void pow(int B[][110], int n)
{
	if(n == 0)
	{
		memcpy(B, I, sizeof I);
		return;
	}
	
	pow(B, n/2);

	matrix(tmp, B, B);

	if(n & 1) matrix(B, tmp, A);
	else matrix(B, tmp, I);
}

void solve()
{
	memset(I, 0, sizeof I);
	for(int i=0; i<mset; ++i) I[i][i] = 1;
	memset(A, 0, sizeof A);
	for(int i=0; i<mset; ++i)
	{
		for(int k=0; k<4; ++k)
		{
			node *now = &memo[i];
			while(now!=root && now->next[k]==NULL) now = now->fail;
			now = now->next[k];
			if(now == NULL) now = root;

			int tmp = now->lv;
			if(now->flag) continue;

			A[i][tmp]++;
		}
	}

	pow(B, n);

	int ans = 0;
	for(int i=0; i<mset; ++i) ans = (ans + B[0][i]) % mod;

	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &m, &n) != EOF)
	{
		init();
		solve();
	}
	return 0;
}
