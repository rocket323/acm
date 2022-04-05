#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;
#define MaxL 1000

struct HP{
	int len, s[200];
	HP(){ len = 1, memset(s, 0, sizeof s); }
/*
	HP operator=(int inte)
	{
		if(inte == 0){ len = 1; s[1] = 0; return (*this); }
		for(int len=0; inte>0;){ s[++len] = inte%10; inte /= 10; }
		return (*this);
	}
*/
	HP add(const HP& b)
	{
		int i; HP c;
		c.len = 1;
		c.s[1] = 0;
		for(i=1; i<=len || i<=b.len || c.s[i]; ++i)
		{
			if(i<=len) c.s[i] += s[i];
			if(i<=b.len) c.s[i] += b.s[i];
			c.s[i+1] = c.s[i] / 10; c.s[i] %= 10;
		}
		c.len = i - 1;
		if(c.len == 0) c.len = 1;
		return c;
	}
	
	void print()
	{
		//printf("%d\n", len);
		for(int i=len; i>=1; --i) printf("%d", s[i]);
		puts("");
	}
};

struct node
{
	int lv, flag;
	node *next[50], *fail;
};

node *root, *Q[MaxL], memo[MaxL];

char s[200], tt[200];
int n, m, p, head, tail, mset;
HP f[100][200];

node * newNode()
{
	node * tmp = &memo[mset++];
	tmp->lv = mset - 1;
	for(int i=0; i<n; ++i) tmp->next[i] = NULL;
	tmp->fail = NULL;
	tmp->flag = 0;
	return tmp;
}

int getID(char ch)
{
	for(int i=0; i<n; ++i)
		if(tt[i]==ch) return i;
	return -1;
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
		for(int i=0; i<n; ++i)
		{
			if(now->next[i]==NULL) continue;

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
	scanf("%s", tt);

	mset = 0;
	root = newNode();

	for(int i=0; i<p; ++i)
	{
		scanf("%s", s);
		addWord(root, s);
	}
	AC();
}

void solve()
{
	//memset(f, 0, sizeof f);

	for(int i=0; i<=m; ++i) for(int j=0; j<mset; ++j)
	{
		f[i][j].len = 1;
		f[i][j].s[1] = 0;
	}

	f[0][0].len = 1;
	f[0][0].s[1] = 1;


	//printf("%d\n", f[0][0].len);

	for(int i=0; i<m; ++i)
	{
		for(int j=0; j<mset; ++j)
		{
			//if(f[i][j] == 0) continue;
			for(int k=0; k<n; ++k)
			{
				node *now = &memo[j];

				while(now!=root && now->next[k]==NULL) now = now->fail;
				now = now->next[k];
				if(now==NULL) now = root;

				int tmp = now->lv;
				if(now->flag) continue;

				f[i+1][tmp] = f[i+1][tmp].add(f[i][j]);
			}
		}
	}

	HP ans;

	ans.len = 1;
	ans.s[1] = 0;


	for(int i=0; i<mset; ++i) if(!memo[i].flag)
	{
		ans = ans.add(f[m][i]);
	}

	ans.print();

}

int main()
{
	while(scanf("%d%d%d", &n, &m, &p) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

