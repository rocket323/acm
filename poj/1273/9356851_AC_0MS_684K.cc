/*
 * =========================================================
 *       Filename:  1273.cpp
 *    Description:  
 *        Created:  2011/9/24 22:29:19
 *         Author:  rocket323
 * =========================================================
 */
#include <stdio.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#define maxl 305
#define maxe 200100
#define INF 0x3f3f3f3f
using namespace std;

struct Edge {
	int idx, flow;
	Edge *next, *opp;
}
adj[maxl], memo[maxe];

int n, m, s, t, h[maxl], vh[maxl], mset;

void addEdgeProcess(int a, int b, int c) {
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->flow = c; ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void addEdge(int a, int b, int c) {
	addEdgeProcess(a, b, c);
	addEdgeProcess(b, a, 0);
	adj[a].next->opp = &memo[mset - 1];
	adj[b].next->opp = &memo[mset - 2];
}

int aug(int now, int m) {
	if(now == t) return m;
	int x = m;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next) {
		if(ptr->flow && h[ptr->idx] + 1 == h[now]) {
			int d = aug(ptr->idx, x < ptr->flow ? x : ptr->flow);
			ptr->flow -= d; ptr->opp->flow += d; x -= d;
			if(h[s] == n || x == 0) return m - x;
		}
	}
	int minh = n;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next) {
		if(ptr->flow && h[ptr->idx] + 1 < minh) {
			minh = h[ptr->idx] + 1;
		}
	}
	if(!--vh[h[now]]) h[s] = n;
	else ++vh[h[now] = minh];
	return m - x;
}

int main() {
	while(scanf("%d%d", &m, &n) != EOF) {
		mset = 0;
		s = 1, t = n;
		for(int i=s; i<=t; ++i) adj[i].next = NULL;
		for(int i=0; i<m; ++i) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, c);
		}
		memset(vh, 0, sizeof vh);
		memset(h, 0, sizeof h);
		int ans = 0;
		vh[0] = n;
		while(h[1] < n) ans += aug(1, INF);
		printf("%d\n", ans);
	}
	return 0;
}
