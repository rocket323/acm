#include <iostream>
#include <cmath>
#define Max 100000000
using namespace std;

int Min, M, N;

void dfs(int floor, int lR, int lH, int V, int S){
	if(S+2*V/lR>=Min) return;
	if(floor==0){
		if(V==0) Min=S;
		return;
	}
	if(V==0) return;
	int r, h, maxh, maxr;
	maxr=sqrt(V);
	if(maxr>lR-1) maxr=lR-1;
	for(r=maxr;r>=floor; r--) {
		maxh=V/(r*r);
		if(maxh>lH-1) maxh=lH-1;
		for(h=maxh; h>=floor; h--) {
			if(floor==M) dfs(floor-1, r, h, V-h*r*r, S+r*r+2*r*h);
			else dfs(floor-1, r, h, V-h*r*r, S+2*r*h);
		}
	}
}

void process( ){
	int i,j,k;
	Min=Max;
	dfs(M,10000,1000,N,0);
	if(Min>=Max) printf("0\n");
	else printf("%d\n",Min);
}

int main(){
	int i,j,k;
//	freopen("1190.in","r",stdin);
	scanf("%d%d",&N,&M);
	process();
//	while(k=1);
	return 0;
}
