#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;
#define maxl 100010

int n, k, s, A[maxl], B[maxl], la[maxl][26], lb[maxl][26], pos[26], p[maxl], mat[26], comat[26];
vector<int> ans;

void calc(int A[], int lst[][26], int n)
{
	for(int i=0; i<n; ++i)
	{
		pos[A[i]] = i;
		for(int j=1; j<=s; ++j) lst[i][j] = pos[j];
	}
}

bool match(int a, int b, int A[], int B[], int la[][26], int lb[][26])
{
	if(mat[B[b]] != -1) return mat[B[b]] == A[a];
	if(comat[A[a]] != -1) return comat[A[a]] == B[b];

	int c1 = 0;
	for(int i=1; i<B[b]; ++i) if(lb[b][i] != -1) c1++;

	int idx = a - b, c2 = 0;
	for(int i=1; i<A[a]; ++i) if(la[a][i] != -1 && la[a][i] >= idx) c2++;

	return c1 == c2;
}

void go_back(int now, int A[], int idx)
{
	memset(comat, -1, sizeof comat);
	if(p[now] == -1)
	{
		memset(mat, -1, sizeof mat);
		return;
	}

	for(int i=1; i<=s; ++i)
	{
		if(lb[p[now]][i] == -1) mat[i] = -1;
		else
		{
			mat[i] = A[lb[p[now]][i] + idx - p[now]];
			comat[A[lb[p[now]][i] + idx - p[now]]] = i;
		}
	}
}

void solve()
{
	for(int i=0; i<n; ++i) scanf("%d", &A[i]);
	for(int i=0; i<k; ++i) scanf("%d", &B[i]);

	memset(pos, -1, sizeof pos);
	calc(A, la, n);
	memset(pos, -1, sizeof pos);
	calc(B, lb, k);

	int j = -1;
	p[0] = -1;
	memset(mat, -1, sizeof mat);
	memset(comat, -1, sizeof comat);
	for(int i=1; i<k; ++i)
	{
		while(j > -1 && !match(i, j + 1, B, B, lb, lb))
		{
			go_back(j, B, i - 1);
			j = p[j];
		}
		if(match(i, j + 1, B, B, lb, lb))
		{
			j++;
			mat[B[j]] = B[i];
			comat[B[i]] = B[j];
		}
		p[i] = j;
	}

	ans.clear();
	j = -1;

	memset(mat, -1, sizeof mat);
	memset(comat, -1, sizeof comat);
	for(int i=0; i<n; ++i)
	{
		while(j > -1 && !match(i, j + 1, A, B, la, lb))
		{
			go_back(j, A, i - 1);
			j = p[j];
		}
		if(match(i, j + 1, A, B, la, lb))
		{
			j++;
			mat[B[j]] = A[i];
			comat[A[i]] = B[j];
		}

		if(j == k - 1)
		{
			ans.push_back(i - k + 2);
			go_back(j, A, i);
			j = p[j];
		}
	}

	printf("%d\n", ans.size());
	for(int i=0; i<ans.size(); ++i)
	{
		printf("%d\n", ans[i]);
	}
}

int main()
{
	while(scanf("%d%d%d", &n, &k, &s) != EOF)
	{
		solve();
	}
	return 0;
}

