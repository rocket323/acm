#include <iostream>
#define MaxL 1e5
#define eps 1e-5
using namespace std;

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

bool check(double x){
	int i,j,k;
	for(i=1;i<=M;i++)
		D[i]=x*T[i]-F[i];
	for(i=1;i<=N;i++) dist[i]=MaxL;
	dist[1]=0;
	for(i=1;i<N;i++){
		for(j=1;j<=M;j++)
			if(dist[A[j]]+D[j]<dist[B[j]])
				dist[B[j]]=dist[A[j]]+D[j];
	}
	for(i=1;i<=M;i++)
		if(dist[B[i]]-dist[A[i]]-D[i]>eps){
			return true;
		}
	return false;
}

inline double Max(double a,double b){
	return (a>b)?a:b;
}

void process(){
	double l=0, r=1000, mid, ans=MaxL;
	while(l<=r+eps){
		mid=(l+r)/2.0;
		if(check(mid)){
			l=mid+eps;
		}
		else r=mid-eps;
	}
	printf("%.2f\n",mid);
}

int main(){
	int i,j,k;
//	freopen("sightsee.10.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}

