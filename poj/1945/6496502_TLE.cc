#include <stdio.h>
#include <cstring>
#define maxl 1000000
#define maxsize 1000000
#define prime (1<<(16)-1)

struct hash
{
	int a, b;
	hash * next;
}
adj[prime], memo[maxsize];

struct node
{
	int a, b, step;
}
Q[maxl];

int n, head, tail, mset;

int find(int a, int b)
{
	int idx = (a * prime % prime + b) % prime;
	hash * ptr = adj[idx].next;

	while(ptr)
	{
		if(ptr->a == a && ptr->b == b) return 1;
		ptr = ptr->next;
	}
	return -1;
}

void Hash(int a, int b)
{
	int idx = (a * prime % prime + b) % prime;

	hash * ptr = &memo[mset++];
	ptr->a = a; ptr->b = b;
	ptr->next = adj[idx].next;
	adj[idx].next = ptr;
}

void push(int a, int b, int step)
{
	if(a > b){ a^=b; b^=a; a^=b; }

	if(b > n) return;

	int k = find(a, b);
	if(k == -1)
	{
		//printf("%d %d %d\n", a, b, step);
		Hash(a, b);
		Q[tail].a = a;
		Q[tail].b = b;
		Q[tail].step = step;
		tail++;
		Hash(a, b);
	}
}

void solve()
{

	mset = 0;
	for(int i=0; i<prime; ++i) adj[i].next = NULL;

	head = tail = 0;
	push(0, 1, 0);

	while(head < tail)
	{
		//printf("%d %d %d\n", Q[head].a, Q[head].b, n);
		if(Q[head].a == n || Q[head].b == n)
		{
			printf("%d\n", Q[head].step);
			return;
		}

		int a = Q[head].a, b = Q[head].b, step = Q[head].step + 1;

		push(a + a, a, step); push(a + a, b, step);
		push(b + b, a, step); push(b + b, b, step);
		push(a + b, a, step); push(a + b, b, step);
		push(b - a, a, step); push(b - a, b, step);
		push(0, a, step); push(0, b, step);

		head++;
	}
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		solve();
	}
	return 0;
}

