#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;
#define maxl 100010

int n, k, s, A[maxl], B[maxl], la[maxl][26], lb[maxl][26], pos[26], p[maxl];
vector<int> ans;

void calc(int A[], int lst[][26], int n)
{
	for(int i=0; i<n; ++i)
	{
		for(int j=1; j<=s; ++j) lst[i][j] = pos[j];
		pos[A[i]] = i;
	}
}

bool match(int a, int b, int A[], int B[], int la[][26], int lb[][26])
{
	int c1 = 0;
	for(int i=1; i<B[b]; ++i) if(lb[b][i] != -1) c1++;

	int idx = a - b, c2 = 0;
	for(int i=1; i<A[a]; ++i) if(la[a][i] != -1 && la[a][i] >= idx) c2++;

	return c1 == c2;
}

void solve()
{
	for(int i=0; i<n; ++i) scanf("%d", &A[i]);
	for(int i=0; i<k; ++i) scanf("%d", &B[i]);

	memset(pos, -1, sizeof pos);
	calc(A, la, n);
	memset(pos, -1, sizeof pos);
	calc(B, lb, k);

	//for(int i=0; i<n; ++i) for(int j=1; j<=s; ++j) printf("nn %d %d %d\n", i, j, la[i][j]);

	int j = -1;
	p[0] = -1;
	for(int i=1; i<k; ++i)
	{
		while(j > -1 && !match(i, j + 1, B, B, lb, lb)) j = p[j];
		if(match(i, j + 1, B, B, lb, lb)) j++;
		p[i] = j;
	}

	/*
	for(int i=0; i<k; ++i) printf("%d ", p[i]);
	puts("");
	*/

	ans.clear();
	j = -1;

	for(int i=0; i<n; ++i)
	{
		while(j > -1 && !match(i, j + 1, A, B, la, lb)) j = p[j];
		if(match(i, j + 1, A, B, la, lb)) j++;

		//printf("%d %d\n", i, j);

		if(j == k - 1)
		{
			ans.push_back(i - k + 2);
			j = p[j];
		}
	}

	printf("%d\n", ans.size());
	for(int i=0; i<ans.size(); ++i) printf("%d\n", ans[i]);
}

int main()
{
	while(scanf("%d%d%d", &n, &k, &s) != EOF)
	{
		solve();
	}
	return 0;
}

