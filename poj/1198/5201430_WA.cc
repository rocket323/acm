#include <stdio.h>
#include <cstring>
#include <set>
#include <iostream>
using namespace std;
#define ll unsigned long long

struct node
{
	unsigned long long id;
	int step;
	int p[4][2];
}
Q[655600];

unsigned long long b[65];
int head, tail, flag;
unsigned long long s, t;
int g1[4][2], g2[4][2];
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
set<unsigned long long> S;
set<unsigned long long>::iterator it;

void init()
{

	b[0] = 1;
	for(int i=1; i<65; ++i) b[i] = (ll)b[i-1] * 2;

	for(int i=1; i<4; ++i) scanf("%d%d", &g1[i][0], &g1[i][1]);
	for(int i=0; i<4; ++i) scanf("%d%d", &g2[i][0], &g2[i][1]);
	for(int i=0; i<4; ++i)
	{
		g1[i][0]--, g1[i][1]--, g2[i][0]--, g2[i][1]--;
	}
	S.clear();
	flag = 0;
}

int check(int r, int c)
{
	return (r>=1 && r<=8 && c>=1 && c<=8);
}

int ocuppy(int now, int r, int c)
{
	for(int i=0; i<4; ++i)
	{
		if(Q[now].p[i][0]==r && Q[now].p[i][1]==c) return 1;
	}
	return 0;
}

void push(ll id, int step, int p[][2])
{
	S.insert(id);

	
	Q[tail].id = id, Q[tail].step = step;
	for(int i=0; i<4; ++i) for(int j=0; j<2; ++j) Q[tail].p[i][j] = p[i][j];
	tail++;
	
	if(id==t && Q[tail-1].step<=8) flag = 1;
}

unsigned long long getID(int p[][2])
{
	unsigned long long ans = 0;
	for(int i=0; i<4; ++i)
	{
		int x = p[i][0] * 8 + p[i][1];
		
		ans = (ll)ans + b[x];
		
	}
	return ans;
}

void move(int now, int idx)
{
	for(int k=0; k<4; ++k)
	{
		int p[4][2];
		
		for(int i=0; i<4; ++i) for(int j=0; j<2; ++j) p[i][j] = Q[now].p[i][j];
		
		int rr = Q[now].p[idx][0] + dr[k];
		int cc = Q[now].p[idx][1] + dc[k];
		
		if(ocuppy(now, rr, cc)) rr += dr[k], cc += dc[k];
		
		if(check(rr, cc))
		{
			
			if(ocuppy(now, rr, cc)) continue;
			p[idx][0] = rr, p[idx][1] = cc;
			unsigned long long id = getID(p);
			
			
			it = S.find(id);
			
			if(it==S.end()) push(id, Q[now].step+1, p);
		}
	}
}

void solve()
{
	head = tail = 0;
	s = getID(g1), t = getID(g2);

	push(s, 0, g1);
	
	
	while(head < tail)
	{
		if(flag){ printf("YES\n"); return; }
		else if(Q[head].step >= 8) break;
		
		for(int i=0; i<4; ++i)
		{
			move(head, i);
		}
		head++;
	}
	printf("NO\n");
	

}

int main()
{
	while(scanf("%d%d", &g1[0][0], &g1[0][1])!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
