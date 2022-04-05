#include <stdio.h>
#include <cstring>
#include <sstream>

int n, w, s, cnt, out[100];
char name[100][100], tmp[100], ch;

void init()
{
	scanf("%d\n", &n);
	for(int i=0; i<n; ++i) gets(name[i]);
	gets(tmp);
	sscanf(tmp, "%d%c%d", &w, &ch, &s);
	w--;
}

void solve()
{
	int p = w;
	memset(out, 0, sizeof out);
	for(int i=1; i<=n; ++i)
	{
		cnt = 0;
		while(true)
		{
			if(!out[p]) cnt++;
			if(cnt == s) break;
			p = (p + 1) % n;
		}
		out[p] = 1;
		puts(name[p]);
	}
}

int main()
{
	init();
	solve();
	return 0;
}

