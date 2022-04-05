#include <iostream>
#define MaxL 100000000
using namespace std;

int l[27],r[27],u[27],d[27], N, P;

int Max(int a, int b){
	return(a>b)?a:b;
}

int Min(int a, int b){
	return(a>b)?b:a;
}

void init(){
	int i,j,k,x,y;
	scanf("%d%d",&N,&P);
	for(i=1;i<=N;i++){
		l[i]=MaxL; r[i]=-MaxL; u[i]=-MaxL; d[i]=MaxL;
		for(j=1;j<=P;j++){
			scanf("%d%d",&x,&y);
			l[i]=Min(l[i], x);
			r[i]=Max(r[i], x);
			u[i]=Max(u[i], y);
			d[i]=Min(d[i], y);
		}
	}
}

bool in(int x, int y, int k){
	return (x>=l[k]&&x<=r[k]&&y>=d[k]&&y<=u[k]);
}

bool process(){
	int i,j,k;
	for(i=1;i<N;i++)
		for(j=i+1;j<=N;j++){
			if(in(l[j], u[j], i)) return false;
			if(in(l[j], d[j], i)) return false;
			if(in(r[j], u[j], i)) return false;
			if(in(r[j], d[j], i)) return false;
		}
	return true;
}			

int main(){
	int i,j,k,T;
//	freopen("1231.in","r",stdin);
	scanf("%d",&T);
	for(i=1;i<=T;i++){
		init();
		if(process())
			printf("YES\n");
		else 
			printf("NO\n");
	}
//	while(k=1);
	return 0;
}
