#include <stdio.h>
#include <cstring>

int n, m, flag;
char T[100010][9], S[110][30];

void init()
{
	scanf("%d%d", &n, &m);

	for(int i=0; i<n; ++i) scanf("%s", T[i]);
	for(int i=0; i<m; ++i) scanf("%s", S[i]);
}

void dfs(int t, int s, int pt, int ps, int lt, int ls)
{
	if(flag) return;
	if(ps == ls)
	{
		int j = pt;
		while(j < lt){ if(T[t][j]!='*') return; j++; }
		flag = 1;
		return;
	}

	if(T[t][pt] == '*')
	{
		dfs(t, s, pt, ps+1, lt, ls);
		if(flag) return;
		dfs(t, s, pt+1, ps+1, lt, ls);
	}
	else if(T[t][pt] == '?')
	{
		dfs(t, s, pt+1, ps+1, lt, ls);
	}
	else
	{
		if(T[t][pt] == S[s][ps]) dfs(t, s, pt+1, ps+1, lt, ls);
	}
}

void solve()
{
	for(int i=0; i<m; ++i)
	{
		int cnt = 0;
		for(int j=0; j<n; ++j)
		{
			flag = 0;
			dfs(j, i, 0, 0, strlen(T[j]), strlen(S[i]));
			if(flag)
			{
				cnt++;
				if(cnt > 1) printf(" ");
				printf("%d", j);
			}
		}
		if(!cnt) puts("Not match");
		else puts("");
	}
}

int main()
{
	init();
	solve();
	return 0;
}

