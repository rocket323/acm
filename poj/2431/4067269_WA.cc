#include <iostream>
#include <algorithm>
#define MaxL 10000000
using namespace std;

struct station{
	int dist, dep;
}E[10001];

int N, cpos, cful;

bool cmp(station A, station B){
	return A.dist>B.dist;
}

void init(){
	int i,j,k;
	scanf("%d", &N);
	for(i=0; i<=N; ++i){
		scanf("%d%d", &E[i].dist, &E[i].dep);
		if(i==N) k=E[i].dist;
	}
	E[N+1].dist=0; E[N+1].dep=MaxL;
	N+=2;
	sort(E, E+N, cmp);
	for(i=0; i<N; ++i)
		if(E[i].dist==k){
			cpos=i;
			cful=E[i].dep;
			break;
		}
}

void process(){
	int i;
	int stop=0, dist;
	int Max=-MaxL, rec=-1;

//	for(i=0; i<N; ++i) cout<<E[i].dist<<' '<<E[i].dep<<endl;
//	cout<<N<<endl;
	while(cpos<N){
		if(E[cpos].dist==0){
			printf("%d\n", stop-1);
			return;
		}
		for(i=cpos+1; i<N; ++i){
			dist=E[cpos].dist-E[i].dist;
			if(dist<=cful)
				if(cful-dist+E[i].dep-E[i].dist>=Max){
					Max=cful-dist+E[i].dep-E[i].dist;
					rec=i;
				}
		}
		if(rec==-1) break;
		cful=cful-(E[cpos].dist-E[rec].dist)+E[rec].dep;
		stop++;
		cpos=rec;
	}
	printf("-1\n");
}

int main(){
//	freopen("2431.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
