#include <stdio.h>
#include <cstring>
#include <vector>
#define maxl 260
using namespace std;

vector<int> gp[maxl];
int t[maxl], vis[maxl], top, n, k;
char word[maxl], tmp[maxl];

void init()
{
	for(int i=0; i<n; ++i)
	{
		scanf("%d", &t[i]);
		t[i]--;
	}
	memset(vis, 0, sizeof vis);

	top = 0;
	for(int i=0; i<n; ++i)
	{
		if(vis[i]) continue;
		int k = i;
		while(!vis[k])
		{
			gp[top].push_back(k);
			vis[k] = 1;
			k = t[k];
		}
		top++;
	}
	scanf("\n");
}

void go()
{
	int len = strlen(word);
	for(int i=len; i<n; ++i) word[i] = ' ';
	word[n] = 0;

	/*
	for(int i=0; i<top; ++i)
	{
		for(int j=0; j<gp[i].size(); ++j) printf("%d ", gp[i][j]);
		puts("");
	}
	*/

	for(int i=0; i<top; ++i)
	{
		int sz = gp[i].size();
		for(int j=0; j<sz; ++j)
		{
			int pre = gp[i][j];
			int now = gp[i][(j + k) % sz];
			tmp[now] = word[pre];
		}
	}

	for(int i=0; i<n; ++i) printf("%c", tmp[i]);
	puts("");
}

void solve()
{
	char str[500];
	gets(str);
	if(str[0] == '0') return;

	k = 0;
	int p = 0;
	while(str[p] != ' ')
	{
		k = k * 10 + str[p] - '0';
		p++;
	}
	strncpy(word, str + p + 1, 1000);

	go();

	solve();
}

int main()
{
	while(scanf("%d", &n), n)
	{
		init();
		solve();
	}
	return 0;
}

