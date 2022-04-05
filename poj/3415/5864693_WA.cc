#include <stdio.h>
#include <cstring>
#include <algorithm>
#define MaxL 300010
#define min(a,b) ((a<b)?a:b)
#define ll long long
using namespace std;

struct node
{
	int last, lcp;
	int sum_1, sum_2, cnt_1, cnt_2;
}stack[MaxL];

int n, m, tot, K;
char S[MaxL], T[MaxL];
int head[MaxL], next[MaxL], rank[MaxL], b[MaxL], L[MaxL], list[MaxL], height[MaxL];
int f[MaxL][20];
int top, sum_1, sum_2;
long long ans;

bool cmp(int i, int j){ return S[i] < S[j]; }

void init()
{
	scanf("%s", S);
	scanf("%s", T);
	n = strlen(S), m = strlen(T);
	strcat(S, "$");
	strcat(S, T);
	strcat(S, "$");
	tot = strlen(S);

	for(int i=1; i<=tot; ++i)
	{
		int j = 0;
		while((1<<j) <= i) ++j;
		j--;
		L[i] = j;
	}
}

void suffix_sort(int n)
{
	for(int i=0; i<n; ++i) list[i] = i;
	sort(list, list+n, cmp);
	b[list[0]] = 0;
	for(int i=1; i<n; ++i)
	{
		if(S[list[i]]==S[list[i-1]]) b[list[i]] = b[list[i-1]];
		else b[list[i]] = i;
	}

	int j;
	for(int h=1; h<n; h<<=1)
	{
		for(int i=0; i<n; ++i) head[i] = next[i] = -1;
		for(int i=n-1; i>=0; --i)
		{
			if(list[i])
			{
				j = list[i] - h; if(j < 0)  j += n;
				next[j] = head[b[j]]; head[b[j]] = j;
			}
		}
		j = n - h; next[j] = head[b[j]]; head[b[j]] = j;
		for(int i=0, k=0; i<n; ++i)
		{
			if(head[i] >= 0) for(j=head[i]; j>=0; j=next[j]) list[k++] = j;
		}
		for(int i=0; i<n; ++i)
		{
			if(i>0 && list[i]+h<n && list[i-1]+h<n && b[list[i]]==b[list[i-1]] && b[list[i]+h]==b[list[i-1]+h])
				rank[list[i]] = rank[list[i-1]];
			else rank[list[i]] = i;
		}
		for(int i=0; i<n; ++i) b[i] = rank[i];
	}
/*
	printf("%s %d\n", S, n);
	for(int i=0; i<n; ++i)
	{
		for(int j=list[i]; j<tot; ++j) printf("%c", S[j]);
		puts("");
	}
*/
}

void get_height(int n)
{
	height[0] = 0;
	for(int i=0; i<n; ++i) rank[list[i]] = i;
	for(int h=0, i=0; i<n; ++i)
	{
		if(rank[i] > 0)
		{
			int j = list[rank[i] - 1];
			while(S[i+h]==S[j+h] && S[i+h]!='$') ++h;
			height[rank[i]] = h;
			if(h > 0) --h;
		}
	}
}

int rmq_ready(int n)
{
	for(int i=0; i<n; ++i) f[i][0] = i;
	for(int j=1; (1<<j)<=n; ++j)
	{
		for(int i=0; (i+(1<<j)-1)<n; ++i)
		{
			int k = i + (1<<(j-1));
			if(height[f[i][j-1]] < height[f[k][j-1]])
				f[i][j] = f[i][j-1];
			else f[i][j] = f[k][j-1];
		}
	}
}

int LCP(int i, int j)
{
	if(i==j) return tot - list[i];
	int log = L[j - i];
	int k = j - (1<<log) + 1;
	return min(height[f[i+1][log]], height[f[k][log]]);
}

void push(int last, int lcp, int cnt_1, int cnt_2, int ts_1, int ts_2)
{
	top++;
	stack[top].last = last; stack[top].lcp = lcp;
	stack[top].cnt_1 = cnt_1; stack[top].cnt_2 = cnt_2;
	stack[top].sum_1 = ts_1; stack[top].sum_2 = ts_2;
	sum_1 += ts_1;
	sum_2 += ts_2;
}

void go(int head, int tail)
{
	int t1, t2, cnt_1, cnt_2;

	sum_1 = sum_2 = 0;
	top = 0;

	//printf("%d %d\n", head, tail);

	if(list[head] < n) push(head, LCP(head, head), 1, 0, 100000, 100000);
	else if(list[head]==n || list[head]==tot-1) push(head, LCP(head, head), 0, 0, 100000, 100000);
	else push(head, LCP(head, head), 0, 1, 100000, 100000);

	for(int i=head+1; i<=tail; ++i)
	{
		t1 = t2 = cnt_1 = cnt_2 = 0;
		//printf("@ %d\n", height[i]);
		while(top && stack[top].lcp>=height[i])
		{
			sum_1 -= stack[top].sum_1;
			sum_2 -= stack[top].sum_2;
			t1 += stack[top].cnt_1 * (height[i] - K + 1);
			t2 += stack[top].cnt_2 * (height[i] - K + 1);
			cnt_1 += stack[top].cnt_1;
			cnt_2 += stack[top].cnt_2;
			top--;
		}

		//printf("n %d %d %d\n", top, sum_1, sum_2);


		//if(list[i] < n) push(i, LCP(i, i), 1, 0, 1000000, 100000);
		//else push(i, LCP(i, i), 0, 1, 100000, 100000);

		if(list[i] < n)
		{
			//printf("a %d %d %lld\n", sum_2, t2, ans);
			ans += sum_2 + t2;
			if(t1 > 0 || t2 > 0) push(i-1, height[i], cnt_1, cnt_2, t1, t2);
			push(i, LCP(i, i), 1, 0, 1000000, 100000);
			//cnt_1++;
		}
		else if(list[i] > n && list[i] < tot - 1)
		{
			//printf("b %d %lld\n", sum_1+t1, ans);
			ans += sum_1 + t1;
			if(t1 > 0 || t2 > 0) push(i-1, height[i], cnt_1, cnt_2, t1, t2);
			push(i, LCP(i, i), 0, 1, 1000000, 100000);
			//cnt_2++;
		}
		/*
		top++;
		stack[top].sum_1 = t1;
		stack[top].sum_2 = t2;
		stack[top].cnt_1 = cnt_1;
		stack[top].cnt_2 = cnt_2;
		stack[top].lcp = h[i];
		stack[top].last = i;
		*/
	}
}

void solve()
{
	suffix_sort(tot);
	get_height(tot);
	rmq_ready(tot);

	int head = 0, tail = 0, fc = 0, sc = 0;
	ans = 0;

/*
	for(int i=0; i<tot; ++i)
	{
		for(int j=i; j<tot; ++j) printf("%d %d %d\n", i, j, LCP(i, j));
	}
*/

	int lcp;
	while(tail < tot)
	{
		while(tail<tot && (lcp = LCP(head, tail))>=K)
		{
			//if(list[tail]>n && list[tail]<tot-1){ /*printf("n %d %d %d\n", tail, fc, fc * (lcp - K + 1)); */ ans += fc * (lcp - K +1); sc++; }
			//if(list[tail] < n){ /*printf("h %d %d %d\n", tail, sc, sc * (lcp - K + 1));*/ ans += sc * (lcp - K + 1); fc++; }
			tail++;
		}

		if(tail - head > 1) go(head, tail-1);

		/*
		while(head<=tail && LCP(head, tail)<K)
		{
			if(list[head] < n) fc--;
			if(list[head]>n && list[head]<tot-1) sc--;
			head++;
		}
		if(head > tail) tail = head;
		*/
		fc = sc = 0;
		while(tail < tot && LCP(tail, tail) < K) tail++;
		head = tail;
	}

	printf("%lld\n", ans);
}

int main()
{
	while(scanf("%d", &K) && K)
	{
		init();
		solve();
	}
	return 0;
}

