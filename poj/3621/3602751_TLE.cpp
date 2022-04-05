#include <iostream>
#define QLen 2000
#define MaxL 1e8
#define eps 1e-5
using namespace std;

int N,M, nex[1001],Med[1001][100];
int g[1001],head,tail, Q[QLen+10],T[1001][100], St[QLen+10];
bool vis[1001];
double dist[1001];
double Bu[1001][100];

void init(){
	int i,j,k,a,b,t;
	scanf("%d%d",&N,&M);
	memset(nex,0,sizeof nex);
	for(i=1;i<=N;i++)
		scanf("%d",&g[i]);
	for(i=1;i<=M;i++){
		scanf("%d%d%d",&a,&b,&t);
		nex[a]++; Med[a][nex[a]]=b;
		T[a][nex[a]]=t;
	}
	for(i=1;i<=N;i++)
		for(j=1;j<=nex[i];j++)
			Bu[i][j]=(g[i]+g[Med[i][j]])/2.0;
}

bool check(double x){
	int i,j,k,a,b;
	double tmp;
	for(i=1;i<=N;i++) dist[i]=MaxL;
	memset(vis,0,sizeof vis);
	head=0; tail=0;
	for(i=1;i<=N;i++){
		tail++;
		Q[tail]=i; vis[i]=1;
		dist[i]=0; St[tail]=1;
	}
	while(head!=tail){
		
		head++;
		if(head>QLen) head=0;
		a=Q[head];
		k=nex[a];
		
		for(i=1;i<=k;i++){
			b=Med[a][i];
			tmp=T[a][i]-x*Bu[a][i];
			if(dist[a]+tmp<dist[b]){
				dist[b]=dist[a]+tmp;
				if(!vis[b]){
					tail++;
					if(tail>QLen) tail=0;
					Q[tail]=b; St[tail]=St[head]+1;
					if(St[tail]>N) return true;
					vis[b]=1;
				}
			}
		}
		vis[a]=0;
		
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
//	freopen("sightsee.10.in","r",stdin);
//	freopen("sight.out","w",stdout);
	init();
	process();
//	while(k=1);
	return 0;
}

