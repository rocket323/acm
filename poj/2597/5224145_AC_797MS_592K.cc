#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll long long

struct node
{
	ll s, t;
}E[81];

ll A[81][81], B[81][81], C[81][81], n;

bool cmp(node A, node B){ return A.t < B.t; }

void make_Gra()
{
	memset(A, 0, sizeof A);
	for(ll i=0; i<n; ++i)
	{
		for(ll j=0; j<n; ++j)
		{
			if(i==j) continue;
			if(E[j].s >= E[i].t) A[i][j] = 1;
		}
	}
}

void matrix(ll C[][81], ll A[][81], ll B[][81])
{
	for(ll i=0; i<n; ++i)
	{
		for(ll j=0; j<n; ++j)
		{
			C[i][j] = 0;
			for(ll k=0; k<n; ++k) C[i][j] += (ll)A[i][k] * B[k][j];
		}
	}
}

void out(ll A[][81])
{
	for(ll i=0; i<n; ++i)
	{
		for(ll j=0; j<n; ++j) printf("%I64d ", A[i][j]);
		printf("\n");
	}
	puts("");
}

void solve()
{
	ll len=0, t = -1000000, ans;
	sort(E, E+n, cmp);
	for(ll i=0; i<n; ++i)
	{
		if(E[i].s >= t)
		{
			len++;
			t = E[i].t;
		}
	}
	make_Gra();

	memset(B, 0, sizeof B);
	for(ll i=0; i<n; ++i) B[i][i] = 1;

	for(ll i=1; i<len; ++i)
	{
		matrix(C, B, A);
		memcpy(B, C, sizeof C);
	}

	ans = 0;
	for(ll i=0; i<n; ++i)
	{
		for(ll j=0; j<n; ++j) ans += C[i][j];
	}
	if(len==1) ans = n;
	printf("%I64d %I64d\n", n - len, ans);
}

int main()
{


	while(scanf("%I64d", &n)!=EOF)
	{
		for(ll i=0; i<n; ++i)
		{
			scanf("%I64d%I64d", &E[i].s, &E[i].t);
			if(E[i].s > E[i].t) swap(E[i].s, E[i].t);
		}
		solve();
	}
	return 0;
}