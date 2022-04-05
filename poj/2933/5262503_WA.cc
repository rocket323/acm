#include <stdio.h>
#include <cstring>

int n, A[31], flag;
int ts, t[31], S[31][31];

void dfs(int now, int dep)
{
	if(flag) return;
	if(ts + n - now + 1 < dep) return;
	if(now==n+1)
	{
		flag = 1;
		return;
	}
	
	for(int i=1; i<=ts; ++i)
	{
		int suc = 0, ls = S[i][0];
		if(S[i][0]==-1)
		{
			if(t[i] > 0)
			{
				if(A[now] > S[i][t[i]]) S[i][0] = 1;
				else if(A[now] < S[i][t[i]]) S[i][0] = 0;
			}
			suc = 1;
		}
		else if(S[i][0]==0 && A[now]<=S[i][t[i]]) suc = 1;
		else if(S[i][0]==1 && A[now]>=S[i][t[i]]) suc = 1;
		
		if(suc)
		{
			S[i][++t[i]] = A[now];
			dfs(now+1, dep);
			if(flag) return;
			--t[i];
			S[i][0] = ls;
		}
	}
	if(ts < dep)
	{
		ts++;
		S[ts][t[ts] = 1] = A[now];
		S[ts][0] = -1;
		dfs(now+1, dep);
		if(flag) return;
		ts--;
	}
}

void solve()
{
	for(int i=1; i<=n; ++i)
	{
		memset(S, -1, sizeof S);
		memset(t, 0, sizeof t);
		ts = 0;
		flag = 0;
		dfs(1, i);
		if(flag){ printf("%d\n", i); break; }
	}
}

int main()
{
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d", &A[i]);
	solve();
	return 0;
}
