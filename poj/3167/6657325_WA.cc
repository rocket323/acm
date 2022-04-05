#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;
#define maxl 100010

int n, k, s, A[maxl], B[maxl], la[maxl][26], lb[maxl][26], pos[26], p[maxl], mat[26];
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

	if(mat[B[b]] != -1) return mat[B[b]] == A[a];
	//if(a == 2 && b == 1) printf("%d %d\n", A[a], B[b]);

	int c1 = 0;
	for(int i=1; i<B[b]; ++i) if(lb[b][i] != -1) c1++;

	int idx = a - b, c2 = 0;
	for(int i=1; i<A[a]; ++i) if(la[a][i] != -1 && la[a][i] >= idx) c2++;

	//if(a == 2 && b == 1) printf("kkkk %d %d\n", c1, c2);
	return c1 == c2;
}

void go_back(int now, int A[], int idx)
{
	if(p[now] == -1)
	{
		memset(mat, -1, sizeof mat);
		return;
	}

	for(int i=1; i<=s; ++i)
	{
		if(lb[p[now] + 1][i] == -1) mat[i] = -1;
		else mat[i] = A[lb[p[now] + 1][i] + idx - p[now]];
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

	/*
	for(int i=0; i<n; ++i) printf("%2d ", A[i]);
	puts("");
	for(int i=0; i<n; ++i) printf("%2d ", la[i][2]);
	puts("");
	for(int i=0; i<k; ++i) printf("%2d ", B[i]);
	puts("");
	//for(int i=0; i<n; ++i) for(int j=1; j<=s; ++j) printf("nn %d %d %d\n", i, j, la[i][j]);
	*/

	int j = -1;
	p[0] = -1;
	memset(mat, -1, sizeof mat);
	for(int i=1; i<k; ++i)
	{
		while(j > -1 && !match(i, j + 1, B, B, lb, lb))
		{
			//if(i == 2) printf("n %d\n", j);
			go_back(j, B, i - 1);
			j = p[j];
		}
		if(match(i, j + 1, B, B, lb, lb)) j++;
		p[i] = j;
		//if(i == 2) printf("x %d\n", j);


		if(j != -1) mat[B[j]] = B[i];

		//printf("%d %d %d\n", i, B[i], mat[B[i]]);
	}

	//for(int i=0; i<k; ++i) printf("%2d ", p[i]);
	//puts("");
	/*
	for(int i=0; i<k; ++i) printf("%d ", p[i]);
	puts("");
	*/

	//printf("n %d %d %d\n", A[18], la[18][2], match(16, 0, A, B, la, lb));

	ans.clear();
	j = -1;

	memset(mat, -1, sizeof mat);
	for(int i=0; i<n; ++i)
	{
		while(j > -1 && !match(i, j + 1, A, B, la, lb))
		{
			go_back(j, A, i - 1);
			j = p[j];
		}
		if(match(i, j + 1, A, B, la, lb)) j++;

		//printf("%d %d\n", i, j);

		if(j != -1) mat[B[j]] = A[i];

		if(j == k - 1)
		{
			ans.push_back(i - k + 2);
			go_back(j, A, i);
			j = p[j];
			/*
			printf("suc %d\n", j);

			puts("\n********************");
			for(int i=1; i<=s; ++i) printf("%d ", mat[i]);
			puts("\n********************");
			*/

		}
	}

	printf("%d\n", ans.size());
	for(int i=0; i<ans.size(); ++i)
	{
		printf("%d\n", ans[i]);
		//for(int j=ans[i]; j<ans[i]+k; ++j) printf("%d ", A[j-1]);
		//puts("");
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

