#include <stdio.h>
#define MaxL 1e5
#define eps 1e-4


int N,M, A[5001], B[5001];
int g[1001],T[5001];
double F[5001], D[5001], dist[1001];

void init(){
	int i,j,k,a,b;
	scanf("%d%d",&N,&M);
	for(i=1;i<=N;i++)
		scanf("%d",&g[i]);
	for(i=1;i<=M;i++){
		scanf("%d%d%d",&a,&b,&T[i]);
		F[i]=(g[a]+g[b])/2.0;
		A[i]=a; B[i]=b;
	}
}

int check(double x){
	int i,j,k;
	for(i=1;i<=M;i++)
		D[i]=T[i]-x*F[i];
	for(i=1;i<=N;i++) dist[i]=MaxL;
	dist[1]=0;
	for(i=1;i<N;i++){
		for(j=1;j<=M;j++)
			if(dist[A[j]]+D[j]<dist[B[j]])
				dist[B[j]]=dist[A[j]]+D[j];
	}
	for(i=1;i<=M;i++)
		if(dist[B[i]]-dist[A[i]]-D[i]>eps){
			return 1;
		}
	return 0;
}

inline double Min(double a,double b){
	return (a<b)?a:b;
}

void process(){
	double l=0, r=1000, mid, ans=MaxL;
	while(l<=r+eps){
		mid=(l+r)/2.0;
		if(check(mid)){
			ans=Min(ans, mid);
			r=mid-eps;
		}
		else l=mid+eps;
	}
	ans=1.0/ans;
	printf("%.2f\n",ans);
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}

