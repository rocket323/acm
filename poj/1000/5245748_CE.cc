#include <stdio.h>
#include <sstream>
#include <cstring>
#include <algorithm>
using namespace std;

struct node
{
	char A[3][101];
}
Q[10000];

int A[3][101];
int l[3], top;
char syb, equ;
int T[101];
int ta[101], tb[101], tc[101];


int ch[10] = {{6,9},{},{3},{2,5},{},{3},{0,9},{},{},{0,6}};
int ad[10] = {{8},{7},{},{9},{},{6,9},{8},{},{},{8}};
int de[10] = {{8},{},{},{},{},{},{5},{1},{6,9},{3,5}};

int ct[10] = {1, 0, 1, 2, 0, 1, 2, 0, 0, 2};
int at[10] = {1, 1, 0, 1, 0, 2, 1, 0, 0, 1};
int dt[10] = {1, 0, 0, 0, 0, 0, 1, 1, 2, 2};

void init()
{
	char S[1000];
	gets(S);
	memset(l, 0, sizeof l);
	
	int p = 0, len = strlen(S);
	for(int i=0; i<3; ++i)
	{
		while(p<len && '0'<=S[p] && S[p]<='9')
		{
			A[i][++l[i]] = S[p] - '0';
			p++;
		}
		p++;
	}	
}

bool hp(int A[], int B[], int C[], int l1, int l2, int l3)
{
	
	for(int i=1; i<=l1; ++i) ta[i] = A[l1 + 1 - i];
	for(int i=1; i<=l2; ++i) tb[i] = B[l2 + 1 - i];
	for(int i=1; i<=l3; ++i) tc[i] = C[l3 + 1 - i];
	
	int L = l1;
	if(l2 > l1) L = l2;
	memset(T, 0, sizeof T);
	for(int i=1; i<=L; ++i)
	{
		T[i] += ta[i] + tb[i];
		T[i+1] += T[i] / 10;
		T[i] %= 10;
	}
	if(T[L+1]!=0) L++;
	
	for(int i=1; i<=L; ++i) if(T[i] != tc[i]) return 0;
	return 1;
}

void move(int top, int A[], int id)
{
	for(int i=0; i<l[id]; ++i) Q[top].A[id][i] = A[i];
	Q[top].A[id][l[id]] = '\0';
}

void handle(int A[], int B[], int C[])
{
	bool flag;
	if(syb=='+')
	{
		flag = hp(A, B, C, l[0], l[1], l[2]);
	}
	else
	{
		flag = hp(B, C, A, l[1], l[2], l[0]);
	}
	if(flag)
	{
		top++;
		//memcpy(Q[top].A[0], A, sizeof A);
		//memcpy(Q[top].A[1], B, sizeof B);
		//memcpy(Q[top].A[2], C, sizeof C);
		move(top, A, 0);
		move(top, B, 1);
		move(top, C, 2);
	}
}

void change(int i1, int j1)
{
	int num = A[i1][j1];
	for(int i=0; i<ct[num]; ++i)
	{
		if(j1==1 && ch[num][i]==0) continue;
		A[i1][j1] = ch[num][i];
		handle(A[0], A[1], A[2]);
		A[i1][j1] = num;
	}
}

void go(int i1, int j1, int i2, int j2)
{
	int n1 = A[i1][j1], n2 = A[i2][j2];
	for(int i=0; i<dt[n1]; ++i)
	{
		if(j2==0 && de[n1][i]==0) continue;
		A[i1][j1] = de[n1][i];
		for(int j=0; j<at[n2]; ++j)
		{
			if(j2==0 && ad[n1][i]==0) continue;
			A[i2][j2] = ad[n2][j];
			handle(A[0], A[1], A[2]);
			A[i2][j2] = n2;
		}
		A[i1][j1] = n1;
	}
}

void check(int i1, int j1, int i2, int j2)
{
	if(i1==i2 && j1==j2) change(i1, j1);
	else go(i1, j1, i2, j2);
}

void out()
{
	if(top==0) printf("-1\n");
	else
	{
		sort(Q+1, Q+1+top, cmp);
		for(int i=1; i<=top; ++i)
		{
			if(i!=1 && strcmp(Q[i].A[0], Q[i-1].A[0])==0 && strcmp(Q[i].A[1], Q[i-1].A[1])==0
			&& strcmp(Q[i].A[2], Q[i-1].A[2])==0) continue;
			printf("%s%c%s=%s\n", Q[i].A[0], Q[i].A[1], Q[i].A[2]);
		}
	}
}

void solve()
{
	top = 0;
	for(int i1=0; i1<3; ++i1)
	for(int j1=1; j1<=l[i1]; ++j1)
	for(int i2=0; i2<3; ++i2)
	for(int j2=1; j2<=l[i2]; ++j2)
	{
		check(i1, j1, i2, j2);
	}
	out();
}

int main()
{
	freopen("A.in", "r", stdin);
	init();
	solve();
	while(1);
	return 0;
}
