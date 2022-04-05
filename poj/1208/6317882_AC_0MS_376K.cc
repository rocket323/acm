#include <stdio.h>
#include <cstring>

int pos[100], A[100][100], top[100], n, a, b;
char s[10], t[10];

void push(int id, int p)
{
	A[p][top[p]++] = id;
	pos[id] = p;
}

void out()
{
	for(int i=0; i<n; ++i)
	{
		printf("%d:", i);
		for(int j=0; j<top[i]; ++j) printf(" %d", A[i][j]);
		puts("");
	}
}

void solve()
{
	for(int i=0; i<n; ++i)
	{
		pos[i] = i;
		top[i] = 1;
		A[i][0] = i;
	}
	while(scanf("%s", s), s[0] != 'q')
	{
		scanf("%d%s%d", &a, t, &b);
		if(pos[a] == pos[b]) continue;

		if(s[0] == 'm' && t[1] == 'n')
		{
			int x = pos[a], y = pos[b];
			while(A[x][top[x]-1] != a){ push(A[x][top[x]-1], A[x][top[x]-1]); top[x]--; }
			while(A[y][top[y]-1] != b){ push(A[y][top[y]-1], A[y][top[y]-1]); top[y]--; }

			push(a, y);
			top[x]--;
		}
		if(s[0] == 'm' && t[1] == 'v')
		{
			int x = pos[a], y = pos[b];
			while(A[x][top[x]-1] != a){ push(A[x][top[x]-1], A[x][top[x]-1]); top[x]--; }

			push(a, y);
			top[x]--;
		}
		if(s[0] == 'p' && t[1] == 'n')
		{
			int x = pos[a], y = pos[b];
			while(A[y][top[y]-1] != b){ push(A[y][top[y]-1], A[y][top[y]-1]); top[y]--; }
			int p = 0;
			while(A[x][p] != a) p++;
			for(int i=p; i<top[x]; ++i) push(A[x][i], y);
			top[x] = p;
		}
		if(s[0] == 'p' && t[1] == 'v')
		{
			int x = pos[a], y = pos[b];
			int p = 0;
			while(A[x][p] != a) p++;
			for(int i=p; i<top[x]; ++i) push(A[x][i], y);
			top[x] = p;
		}

	}
	out();
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		solve();
	}
	return 0;
}

