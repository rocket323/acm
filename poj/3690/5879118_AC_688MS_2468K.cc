#include <stdio.h>
#include <cstring>
#include <iostream>
#include <map>
#define ll long long
#define MaxL 6010
using namespace std;

struct node
{
	int cnt, cur;
	node *fail;
	map<ll, int> next;
};

node *root, *Q[MaxL], memo[MaxL];

map<ll, int> :: iterator it;
int n, m, t, p, q, mset, head, tail;
char S[1010][1010];
char T[101][51][51];
long long pat[101][51], base[51], tmp[1010], text[1010];
int mat[101], ans;

node * newNode()
{
	node *ptr = &memo[mset++];
	ptr->cnt = 0;
	ptr->cur = -1;
	ptr->fail = NULL;
	ptr->next.clear();

	return ptr;
}

void addWord(long long a[])
{
	node *now = root;
	for(int i=0; i<p; ++i)
	{
		it = now->next.find(a[i]);
		int pt;
		if(it == now->next.end())
		{
			newNode();
			now->next.insert(make_pair(a[i], mset - 1));
			pt = mset - 1;
		}
		else pt = it->second;

		now = &memo[pt];
	}
	now->cnt++;
}

void AC()
{
	tail = 1;
	Q[head = 0] = root;
	while(head < tail)
	{
		node *now = Q[head++];
		for(it=now->next.begin(); it!=now->next.end(); it++)
		{
			node *p = now->fail;
			while(p!=NULL && p->next.find(it->first) == p->next.end()) p = p->fail;
			if(p==NULL) (&memo[it->second])->fail = root;
			else (&memo[it->second])->fail = &memo[p->next[it->first]];

			Q[tail++] = (&memo[it->second]);
		}
	}
}

void init()
{
	mset = 0;
	root = newNode();

	for(int i=0; i<n; ++i) scanf("%s", S[i]);

	for(int i=0; i<t; ++i)
	{
		for(int j=0; j<p; ++j)
		{
			scanf("%s", T[i][j]);
			pat[i][j] = 0;
			for(int k=0; k<q; ++k) pat[i][j] = pat[i][j] + (ll)base[k] * (T[i][j][k]=='*');
		}
	}

	for(int i=0; i<t; ++i) addWord(pat[i]);

	AC();
}

bool match(int pos)
{
	node *now = root;
	for(int i=0; i<n; ++i)
	{
		while(now!=root && now->next.find(text[i]) == now->next.end()) now = now->fail;
		if(now->next.find(text[i]) == now->next.end()) now = root;
		else now = &memo[now->next[text[i]]];

		node *tmp = now;
		while(tmp)
		{
			if(tmp->cnt && tmp->cur == -1)
			{
				ans += tmp->cnt;
				tmp->cur = pos;
			}
			tmp = tmp->fail;
		}
	}
}

void solve(int tc)
{
	ans = 0;
	for(int i=0; i<n; ++i)
	{
		text[i] = 0;
		for(int j=0; j<q; ++j) text[i] = text[i] + (ll)base[j] * (S[i][j] == '*');

	}
	match(0);

	for(int i=1; i<=m-q; ++i)
	{
		for(int j=0; j<n; ++j) text[j] = text[j] / 2 + (ll)base[q - 1] * (S[j][i+q-1] == '*');
		match(i);
	}

	printf("Case %d: %d\n", tc, ans);
}

int main()
{
	int tc = 0;
	base[0] = 1;
	for(int i=1; i<51; ++i) base[i] = (ll)base[i-1] * 2;

	while(scanf("%d%d%d%d%d", &n, &m, &t, &p, &q) && n)
	{
		init();
		solve(++tc);
	}
	return 0;
}

