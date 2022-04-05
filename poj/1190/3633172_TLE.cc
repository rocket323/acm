#include <iostream>
#define Max 100000000
using namespace std;

int Min, M, N;

void dfs(int floor, int lR, int lH, int V, int S){
	if(floor==0){
		if(S<Min&&V==0) Min=S;
		return;
	}
	int r, h;
	for(r=lR-1;r>=floor; r--) if(r*r<=V)
		for(h=lH-1;h>=floor; h--) if(h*r*r<=V){
			if(floor==M) dfs(floor-1, r, h, V-h*r*r, S+r*r+2*r*h);
			else dfs(floor-1, r, h, V-h*r*r, S+2*r*h);
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
