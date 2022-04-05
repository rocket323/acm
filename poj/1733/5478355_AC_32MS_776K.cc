#include <stdio.h>
#include <cstring>
#include <algorithm>
#define MaxL 10010
using namespace std;

struct node
{
	int s, t, c, idx;
}
E[MaxL];

int A[MaxL], B[MaxL], top, n, m, l;
int p[MaxL], opp[MaxL], flag;

void init()
{
	char S[10];
	scanf("%d", &m);
	top = 0;
	for(int i=1; i<=m; ++i)
	{
		scanf("%d%d%s", &E[i].s, &E[i].t, S);
		E[i].idx = i;
		if(S[0]=='o') E[i].c = 1;
		else E[i].c = 0;
		A[++top] = E[i].s;
		A[++top] = E[i].t;
	}
	sort(A+1, A+1+top);
	top = 0;
	for(int i=1; i<=2*m; ++i)
	{
		if(top==0 || A[i]!=B[top]) B[++top] = A[i];
	}
}

int getID(int x)
{
	int l=1, r=top, mid;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(B[mid]==x) return mid;
		else if(B[mid] > x) r = mid - 1;
		else l = mid + 1;
	}
}

int find(int now)
{
	if(p[now]==now) return now;
	else return p[now] = find(p[now]);
}

int unin(int x, int y)
{
	if(x!=-1 && y!=-1)
	{
		p[y] = x;
		if(opp[y] == x) flag = 0;
		return x;
	}
	else return (x!=-1) ? x : y;
}

void solve()
{
	for(int i=0; i<=top; ++i) p[i] = i;
	memset(opp, -1, sizeof opp);
	int i;
	flag = 1;
	for(i=1; i<=m; ++i)
	{
		int a, b, x, y;
		a = find(getID(E[i].s)-1);
		b = find(getID(E[i].t));
		x = opp[a];
		y = opp[b];
		if(E[i].c==0)
		{
			int k1 = unin(a, b);
			int k2 = unin(x, y);
			if(k2 != -1)
			{
				opp[k1] = k2;
				opp[k2] = k1;
			}
		}
		else
		{
			if(a == b) flag = 0;
			else
			{
				int k1 = unin(a, y);
				int k2 = unin(b, x);
				opp[k1] = k2;
				opp[k2] = k1;
			}
		}
		if(!flag) break;
	}
	printf("%d\n", i-1);
}

int main()
{
	while(scanf("%d", &l) != EOF)
	{
		init();
		solve();
	}
	return 0;
}
