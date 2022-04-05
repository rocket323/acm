#include <iostream>
#include <algorithm>
#include <set>
#define MaxN 100010

using namespace std;

struct Node{
	long long p, g;
}Cow[MaxN], Food[MaxN];

long long N, M;
set<pair<long long, long long> > S;
set<pair<long long, long long> >::iterator now;

bool cmp(Node A, Node B){
	return (A.g<B.g);
}

void init(){
	long long i,j,k;
	scanf("%lld%lld", &N, &M);
	for(i=0; i<N; ++i) scanf("%lld%lld", &Cow[i].p, &Cow[i].g);
	for(i=0; i<M; ++i) scanf("%lld%lld", &Food[i].p, &Food[i].g);
	sort(Cow, Cow+N, cmp);
	sort(Food, Food+M, cmp);
	


	
}

void process(){
	long long i,j,k, pos=M-1, ans=0;
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
	if(i!=-1) cout<<-1<<endl;
	else printf("%d\n", ans);
}

int main(){
	long long i,j,k;
//	freopen("3622.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
