#include <iostream>
#include <algorithm>
#include <set>
#define MaxN 100010

using namespace std;

struct Node{
	int p, g;
}Cow[MaxN], Food[MaxN];

int N, M;
set<pair<int, int> > S;
set<pair<int, int> >::iterator now;
bool vis[MaxN];

bool cmp(Node A, Node B){
	return (A.g<B.g);
}

void init(){
	int i,j,k;
	scanf("%d%d", &N, &M);
	for(i=0; i<N; ++i) scanf("%d%d", &Cow[i].p, &Cow[i].g);
	for(i=0; i<M; ++i) scanf("%d%d", &Food[i].p, &Food[i].g);
	sort(Cow, Cow+N, cmp);
	sort(Food, Food+M, cmp);
	
/*	cout<<"--------------"<<endl;
	for(i=0; i<N; ++i) cout<<Cow[i].g<<' '<<Cow[i].p<<endl;
	cout<<"--------------"<<endl;
	for(i=0; i<M; ++i) cout<<Food[i].g<<' '<<Food[i].p<<endl;
	cout<<"--------------"<<endl;*/

	
}

void process(){
	int i,j,k, pos=M-1, ans=0;
	for(i=N-1; i>=0; --i){
		while(Food[pos].g>=Cow[i].g&&pos>=0){
			S.insert(make_pair(Food[pos].p, pos));
			pos--;
		}
		now=S.lower_bound(make_pair(Cow[i].p, -1));

		if(now==S.end()) break;
		ans+=now->first;
		S.erase(now);
	}
	printf("%d\n", ans);
}

int main(){
	int i,j,k;
//	freopen("3622.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
