#include <iostream>
#define QLen 2005
#define MaxL 1e7
#define eps 1e-4
using namespace std;

int N,M, nex[1001],Med[1001][100];
int g[1001],head,tail, Q[QLen+10],T[1001][100], cnt[1001];
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

}

bool check(double x){
	int i,j,k,a,b;
	double tmp;
	head=0; tail=0;
	for(i=1;i<=N;i++){
		tail++;
		Q[tail]=i; vis[i]=1;
		dist[i]=0; cnt[i]=0;
	}

	while(head!=tail){
		
		head++;
		if(head>QLen) head=0;
		a=Q[head];
		
		for(i=1;i<=nex[a];i++){
			b=Med[a][i];
			
			if(dist[a]+Bu[a][i]<dist[b]){
				dist[b]=dist[a]+Bu[a][i];
				if(!vis[b]){
					tail++;
					if(tail>QLen) tail=0;
					Q[tail]=b; cnt[b]=cnt[a]+1;
					if(cnt[b]>N) return true;
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
	int i,j,k;
	double l=0, r=1000, mid, ans=MaxL;
	while(r-l>eps){
		mid=(l+r)/2.0;
		for(i=1;i<=N;i++)
			for(j=1;j<=nex[i];j++)
				Bu[i][j]=mid*T[i][j]-(double)g[Med[i][j]];
		if(check(mid)){
			l=mid;
		}
		else r=mid;
	}
	if(mid>eps)
		printf("%.2f\n",mid);
	else printf("0\n");
}

int main(){
	int i,j,k;
//	freopen("sightsee.1.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}

