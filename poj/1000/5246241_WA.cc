#include <stdio.h>
#include <sstream>
#include <cstring>
#include <algorithm>
using namespace std;

struct node
{
	char A[3][101];
	char str[200];
}
Q[5000];

int A[3][101];
int l[3], top;
char syb, equ;
int T[101];
int ta[101], tb[101], tc[101];


int ch[10][5] = {{6,9},{},{3},{2,5},{},{3},{0,9},{},{},{0,6}}; //add one and dec one change to
int ad[10][5] = {{8},{7},{},{9},{},{6,9},{8},{},{},{8}}; //add one change to
int de[10][5] = {{},{},{},{},{},{},{5},{1},{0,6,9},{3,5}}; //dec one change to

int ct[10] = {2, 0, 1, 2, 0, 1, 2, 0, 0, 2}; //change one count
int at[10] = {1, 1, 0, 1, 0, 2, 1, 0, 0, 1}; //add one count
int dt[10] = {0, 0, 0, 0, 0, 0, 1, 1, 3, 2}; //dec one count

void show(int A[], int len)
{
	//printf("**********\n");
	for(int i=1; i<=len; ++i) printf("%d", A[i]);
	//printf("**********\n");
	printf("\n");
}

void init()
{
	char S[1000];
	scanf("%s", S);
	memset(l, 0, sizeof l);
	
	int p = 0, len = strlen(S);
	for(int i=0; i<3; ++i)
	{
		while(p<len && '0'<=S[p] && S[p]<='9')
		{
			A[i][++l[i]] = S[p] - '0';
			p++;
		}
		if(i==0) syb = S[p];
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

	if(l3 != L) return 0;
	
	for(int i=1; i<=L; ++i) if(T[i] != tc[i]) return 0;
	return 1;
}

void move(int top, int A[], int id)
{
	for(int i=0; i<l[id]; ++i)
	{
		Q[top].A[id][i] = A[i+1] + '0';
	}
	Q[top].A[id][l[id]] = '\0';
}

void handle(int AA[], int BB[], int CC[])
{
	bool flag;
	if(syb=='+')
	{
		flag = hp(AA, BB, CC, l[0], l[1], l[2]);
	}
	else
	{
		flag = hp(BB, CC, AA, l[1], l[2], l[0]);
	}
	if(flag)
	{
		top++;
		int p = 0;
		for(int i=0; i<3; ++i)
		{
			for(int j=1; j<=l[i]; ++j)Q[top].str[p++] = A[i][j] + '0';
			if(i==0) Q[top].str[p++] = syb;
			else if(i==1) Q[top].str[p++] = '=';
		}
		Q[top].str[p++] = '\0';
	}
}

void change(int i1, int j1)
{
	int num = A[i1][j1];
	for(int i=0; i<ct[num]; ++i)
	{
		if(l[i1]>1 && j1==1 && ch[num][i]==0) continue;
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
		if(l[i1]>1 && j1==1 && de[n1][i]==0) continue;
		A[i1][j1] = de[n1][i];
		for(int j=0; j<at[n2]; ++j)
		{
			if(l[i2]>1 && j2==1 && ad[n1][j]==0) continue;
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

bool cmp(node A, node B)
{
	return (strcmp(A.str, B.str)<0);
}

void out()
{
	if(top==0) printf("-1\n");
	else
	{
		sort(Q+1, Q+1+top, cmp);
		for(int i=1; i<=top; ++i)
		{
			//if(i!=1 && strcmp(Q[i].A[0], Q[i-1].A[0])==0 && strcmp(Q[i].A[1], Q[i-1].A[1])==0
			//&& strcmp(Q[i].A[2], Q[i-1].A[2])==0) continue;
			if(i!=1 && strcmp(Q[i].str, Q[i-1].str)==0) continue;
			//printf("%s%c%s=%s\n", Q[i].A[0], syb, Q[i].A[1], Q[i].A[2]);
			printf("%s\n", Q[i].str);
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
	init();
	solve();
	return 0;
}
