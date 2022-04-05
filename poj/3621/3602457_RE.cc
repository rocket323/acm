#include <iostream>
#define MaxL 1e7
#define eps 1e-6
using namespace std;

int N,M, A[5001], B[5001],nex[1001],Med[1001][1001];
int g[1001],head,tail, Q[600000],T[1001][1001], St[600000];
bool vis[1001];
double dist[1001];

void init(){
	int i,j,k,a,b,t;
	scanf("%d%d",&N,&M);
	memset(nex,0,sizeof nex);
	for(i=1;i<=N;i++)
		scanf("%d",&g[i]);
	for(i=1;i<=M;i++){
		scanf("%d%d%d",&a,&b,&t);
		A[i]=a; B[i]=b;
		nex[a]++; Med[a][nex[a]]=b;
		T[a][nex[a]]=t;
	}
}

bool check(double x){
	int i,j,k,a,b;
	double tmp;
	for(i=1;i<=N;i++) dist[i]=MaxL;
	memset(vis,0,sizeof vis);
	dist[1]=0; vis[1]=1;
	Q[1]=1; head=tail=1; St[1]=0;
	while(head<=tail){
		a=Q[head];
		k=nex[a];
		if(St[head]>N) return true;
		for(i=1;i<=k;i++){
			b=Med[a][i];
			tmp=T[a][i]-x*(g[a]+g[b])/2.0;
			if(dist[a]+tmp<dist[b]){
				dist[b]=dist[a]+tmp;
				if(!vis[b]){
					tail++;
					Q[tail]=b; St[tail]=St[head]+1;
					vis[b]=1;
				}
			}
		}
		vis[a]=0;
		head++;
	}

	return false;
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
//	freopen("sightsee.8.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}

