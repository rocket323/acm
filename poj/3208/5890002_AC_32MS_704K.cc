#include <stdio.h>
#include <cstring>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

struct node
{
	int num, idx;
	node *next;
}
adj2[200], adj[7], memo[1000];

struct msg
{
	int num, idx;
}tmp[100];

int f[200][11];
int n, mset, vis[10];
set<int> S;
set<int> :: iterator it;
int Q[100], head, tail, A[100], B[100], ta, tb, top;

void add(node adj[], int a, int b, int num)
{
	node *ptr = &memo[mset++];
	ptr->idx = b; ptr->num = num;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void decode(int A[], int& top, int k)
{
	top = 0;
	for(int i=0; i<7; ++i)
		if(k & (1<<i)) A[top++] = i;
}

int incode(int vis[])
{
	int id = 0;
	for(int i=0; i<7; ++i)
		if(vis[i]) id |= (1<<i);
	return id;
}

void transfer(int A[], int top, int vis[], int num, int& cnt)
{
	for(int i=0; i<top; ++i)
	{
		for(node *ptr=adj[A[i]].next; ptr; ptr=ptr->next)
		{
			if(ptr->num != num) continue;
			vis[ptr->idx] = 1;
			cnt++;
		}
	}
}

void closure(int vis[])
{
	int flag = 1;
	while(flag)
	{
		flag = 0;
		for(int i=0; i<7; ++i)
		{
			if(!vis[i]) continue;
			for(node *ptr=adj[i].next; ptr; ptr=ptr->next)
			{
				if(ptr->num != 10) continue;
				if(!vis[ptr->idx])
				{
					flag = 1;
					vis[ptr->idx] = 1;
				}
			}
		}
	}
}

void nfa_to_dfa()
{
	S.clear();

	tail = 1;
	Q[head = 0] = 1;

	S.insert(1);

	/*
	for(int i=0; i<7; ++i)
	{
		printf("%d : ", i);
		for(node *ptr=adj[i].next; ptr; ptr=ptr->next)
		{
			printf("%d %d ", ptr->num, ptr->idx);
		}
		puts("");
	}
	*/

	while(head < tail)
	{
		decode(A, ta, Q[head]);
		//printf("n %d %d\n", head, Q[head]);

		/*
		if(head == 0)
		{
			printf("%d : ", ta);
			for(int j=0; j<ta; ++j) printf("%d ", A[j]);
			puts("");
		}
		*/
		for(int i=0; i<10; ++i)
		{
			int cnt = 0;
			memset(vis, 0, sizeof vis);
			transfer(A, ta, vis, i, cnt);
			
			
			/*
			if(head == 0 && i == 0)
			{
				for(int j=0; j<7; ++j) printf("%d ", vis[j]);
				puts("");
			}
			*/
			

			if(cnt == 0) continue;
			closure(vis);
			int k = incode(vis);

			//printf("%d %d %d\n", Q[head], i, k);
		
			add(adj2, Q[head], k, i);


			if(S.find(k) == S.end())
			{
				S.insert(k);
				Q[tail++] = k;
			}
		}
		head++;
	}
}

void init()
{
	mset = 0;
	for(int i=0; i<7; ++i) adj[i].next = NULL;
	for(int i=0; i<7; ++i) adj2[i].next = NULL;

	for(int i=1; i<10; ++i) add(adj, 0, 1, i);
	for(int i=0; i<10; ++i) add(adj, 1, 2, i);
	for(int i=0; i<10; ++i) add(adj, 5, 6, i);
	add(adj, 2, 3, 6);
	add(adj, 3, 4, 6);
	add(adj, 4, 5, 6);
	add(adj, 1, 2, 10);
	add(adj, 2, 1, 10);
	add(adj, 5, 6, 10);
	add(adj, 6, 5, 10);

	add(adj, 0, 3, 6);

	nfa_to_dfa();

	/*
	cout << S.size() << endl;
	for(it=S.begin(); it!=S.end(); it++)
	{
		printf("%d ", *it);
	}
	puts("");
	*/
}

int dp(int now, int len)
{
	if(f[now][len] != -1) return f[now][len];

	if(len == 0)
	{
		if(now==102 || now==110 || now==126) return f[now][len] = 1;
		else return f[now][len] = 0;
	}

	f[now][len] = 0;
	for(node *ptr=adj2[now].next; ptr; ptr=ptr->next)
	{
		f[now][len] += dp(ptr->idx, len-1);
	}

	//printf("%d %d %d\n", now, len, f[now][len]);

	return f[now][len];
}

bool cmp(msg A, msg B){ return A.num < B.num; }

void go(int now, int len, int n)
{
	int i;
	top = 0;

	if(len <= 0) return;

	for(node *ptr=adj2[now].next; ptr; ptr=ptr->next)
	{
		tmp[top].num = ptr->num;
		tmp[top].idx = ptr->idx;
		top++;
	}
	sort(tmp, tmp+top, cmp);

	for(int i=0; i<top; ++i)
	{
		int k = dp(tmp[i].idx, len-1);
		if(k < n) n -= k;
		else
		{
			printf("%d", tmp[i].num);
			go(tmp[i].idx, len-1, n);
			break;
		}
	}
}

void solve()
{
	/*
	if(n == 1)
	{
		puts("666");
		return;
	}
	*/

	memset(f, -1, sizeof f);

	/*
	
	for(it=S.begin(); it!=S.end(); it++)
	{
		printf("%d : ", *it);
		for(node *ptr=adj2[*it].next; ptr; ptr=ptr->next)
		{
			printf("%d %d ", ptr->num, ptr->idx);
		}
		puts("");
	}
	*/
	
	int len = 0, sum = 0;

	for(int i=1; ; ++i)
	{
		int k = dp(1, i);
		if(k < n) n -= k;
		else
		{
			len = i;
			break;
		}
	}

	//printf("%d\n", len);

	go(1, len, n);
	puts("");

	//printf("%d %d\n", dp(1, 4) , dp(1, 5));
	//printf("%d\n", len);

}

int main()
{
	int t;
	init();
	scanf("%d", &t);

	while(t--)
	{
		scanf("%d", &n);
		solve();
	}
	return 0;
}

