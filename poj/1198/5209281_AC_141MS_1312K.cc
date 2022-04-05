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
Q[2][6550];

unsigned long long b[65];
int head[2], tail[2];
unsigned long long s, t;
int g1[4][2], g2[4][2];
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
set<unsigned long long> S[2];
set<unsigned long long>::iterator it[2];

int C[2],getIt;

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
	S[0].clear();
	S[1].clear();
}

int check(int r, int c)
{
	return (r>=0 && r<8 && c>=0 && c<8);
}

int ocuppy(int key, int now, int r, int c)
{
	for(int i=0; i<4; ++i)
	{
		if(Q[key][now].p[i][0]==r && Q[key][now].p[i][1]==c) return 1;
	}
	return 0;
}

void push(int key, ll id, int step, int p[][2])
{
	S[key].insert(id);
	C[key]++;
	
	Q[key][tail[key]].id = id, Q[key][tail[key]].step = step;
	for(int i=0; i<4; ++i) for(int j=0; j<2; ++j) Q[key][tail[key]].p[i][j] = p[i][j];
	tail[key]++;
	
	int opp = key^1;
	it[opp] = S[opp].find(id);
	if(it[opp]!=S[opp].end()) getIt = 1;
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

void move(int key, int now, int idx)
{
	for(int k=0; k<4; ++k)
	{
		int p[4][2];
		
		for(int i=0; i<4; ++i) for(int j=0; j<2; ++j) p[i][j] = Q[key][now].p[i][j];
		int rr = Q[key][now].p[idx][0] + dr[k];
		int cc = Q[key][now].p[idx][1] + dc[k];
		
		if(ocuppy(key, now, rr, cc)) rr += dr[k], cc += dc[k];
		if(check(rr, cc))
		{
			if(ocuppy(key, now, rr, cc)) continue;
			p[idx][0] = rr, p[idx][1] = cc;
			unsigned long long id = getID(p);
			
			it[key] = S[key].find(id);
			if(it[key]==S[key].end()) push(key, id, Q[key][now].step+1, p);
		}
	}
}

void solve()
{
	head[0] = head[1] = tail[0] = tail[1] = 0;
	s = getID(g1), t = getID(g2);
	push(0, s, 0, g1);
	push(1, t, 0, g2);
	getIt = 0;
	while(true)
	{
		if(getIt){ printf("YES\n"); return; }
		int t = -1;
		if(Q[0][head[0]].step<4 && Q[1][head[1]].step<4)
		{
			if(C[0] < C[1]) t = 0;
			else t = 1;
		}
		else if(Q[0][head[0]].step<4) t = 0;
		else if(Q[0][head[1]].step<4) t = 1;
		
		if(t == -1) break;
		for(int i=0; i<4; ++i) move(t, head[t], i);
		head[t]++;
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
