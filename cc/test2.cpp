// #include <bits/stdc++.h>
// iostream is too mainstream
#include <cstdio>
// bitch please
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <cmath>
#include <iomanip>
#include <time.h>
#define dibs reserve
#define OVER9000 1234567890123456789LL
#define ALL_THE(CAKE,LIE) for(auto LIE =CAKE.begin(); LIE != CAKE.end(); LIE++)
#define tisic 47
#define soclose 1e-8
#define chocolate win
// so much chocolate
#define patkan 9
#define ff first
#define ss second
#define abs(x) ((x < 0)?-(x):x)
#define uint unsigned int
#define dbl long double
#define pi 3.14159265358979323846
using namespace std;
// mylittledoge

typedef long long cat;

#ifdef DONLINE_JUDGE
	// palindromic tree is better than splay tree!
	#define lld I64d
#endif

bool DFS_mxedge(int R, int par, auto &G, int goal, int &g) {
	// is it above the goal?
	if(R == goal) return 1;
	ALL_THE(G[R],it) if(it->ff != par)
		if(DFS_mxedge(it->ff,R,G,goal,g)) {
			g =max(g,it->ss);
			return 1;
		}
	return 0;
}

void DFS_comps(int R, int par, auto &G, auto &inCc, auto &C) {
	inCc[R] =1;
	C.push_back(R);
	ALL_THE(G[R],it) if(it->ff != par)
		DFS_comps(it->ff,R,G,inCc,C);
}

void DFS(int R, int par, auto &G, auto &V, auto &Rt) {
	ALL_THE(G[R],it) if(it->ff != par) {
		DFS(it->ff,R,G,V,Rt);
		Rt[it->ss] =min(Rt[it->ss],V[it->ff]);
		V[R] =min(V[R],V[it->ff]);
	}
}

int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(10);
	int T, N =10010;
	cin >> T;
	while(T--) {
		int M;
		cin >> M;
		vector< pair<int,int> > E(M);
		for(int i =0; i < M; i++) {
			cin >> E[i].ff >> E[i].ss;
			E[i].ff--, E[i].ss--;
		}
		vector<int> ans(M,0), R(M,M);

		vector<bool> inT(M,0);
		vector< vector<int> > comp(N);
		vector<int> inC(N);
		for(int i =0; i < N; i++) {
			inC[i] =i;
			comp[i].push_back(i);
		}
		vector< vector< pair<int,int> > > G(N);

		vector<bool> inC1(N,0),inC2(N,0);
		vector<int> V(N), C1, C2;
		for(int L =M-1; L >= 0; L--) {
			int u =E[L].ff, v =E[L].ss;
			inT[L] =1;

			if(inC[u] != inC[v]) {
				// merge components
				u =inC[u], v =inC[v];
				if(comp[u].size() < comp[v].size()) swap(u,v);
				ALL_THE(comp[v],it) {
					comp[u].push_back(*it);
					inC[*it] =u;
				}
				u =E[L].ff, v =E[L].ss;
			}
			else {
				// remove an edge from T
				int g =0;
				DFS_mxedge(u,u,G,v,g);
				inT[g] =0;
				int a =E[g].ff, b =E[g].ss;
				for(int i =0; i < (int)G[a].size(); i++) if(G[a][i].ss == g) {
					swap(G[a][i],G[a].back());
					G[a].pop_back();
					break;
				}
				for(int i =0; i < (int)G[b].size(); i++) if(G[b][i].ss == g) {
					swap(G[b][i],G[b].back());
					G[b].pop_back();
					break;
				}
			}
			DFS_comps(u,u,G,inC1,C1);
			DFS_comps(v,v,G,inC2,C2);
			G[u].push_back(make_pair(v,L));
			G[v].push_back(make_pair(u,L));

			for(int i =L; i < M; i++) V[E[i].ff] =V[E[i].ss] =M;
			for(int i =L+1; i < M; i++) if(!inT[i]) {
				R[i] =i;
				if(inC2[E[i].ff] && inC1[E[i].ss]) swap(E[i].ff,E[i].ss);
				if(inC1[E[i].ff] && inC2[E[i].ss]) {
					R[L] =min(R[L],i);
					V[E[i].ff] =min(V[E[i].ff],i);
					V[E[i].ss] =min(V[E[i].ss],i);
				}
			}

			DFS(u,v,G,V,R);
			DFS(v,u,G,V,R);

			ALL_THE(C1,it) inC1[*it] =0;
			ALL_THE(C2,it) inC2[*it] =0;
			C1.clear();
			C2.clear();

			for(int i =L; i < M; i++) ans[i] +=M-R[i];
		}

		for(int i =0; i < M; i++) cout << ans[i] << ((i == M-1)?"\n":" ");
	}
}

// look at my code
// my code is amazing
