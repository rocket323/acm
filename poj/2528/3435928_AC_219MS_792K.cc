#include <iostream>
#define MaxL 20010
using namespace std;

int rank[MaxL],pos[MaxL],p1[MaxL],p2[MaxL],n,tot,A[MaxL];
int col[MaxL];
bool can[MaxL];

void qsort(int s, int t){
	int x=A[pos[(s+t)/2]];
	int i,j,tmp;
	i=s; j=t;
	while(i<j){
		while(A[pos[i]]<x) i++;
		while(A[pos[j]]>x) j--;
		if(i<=j){
			tmp=pos[i]; pos[i]=pos[j]; pos[j]=tmp;
			i++; j--;
		}
	}
	if(i<t) qsort(i,t);
	if(s<j) qsort(s,j);
}

void init(){
	int i,j,k,a,b;
	tot=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d%d",&a,&b);
		tot++; p1[i]=tot; A[tot]=a;
		tot++; p2[i]=tot; A[tot]=b;
	}
	for(i=1;i<=tot;i++) pos[i]=i;
	qsort(1,tot);
	rank[pos[1]]=1;
	for(i=2;i<=tot;i++)
		if(A[pos[i]]==A[pos[i-1]]) rank[pos[i]]=rank[pos[i-1]];
		else rank[pos[i]]=rank[pos[i-1]]+1;
}

void process(){
	int i,j,k,a,b,ans,maxn=0;
	memset(col,0,sizeof col);	
	for(i=1;i<=n;i++){
		a=rank[p1[i]]; b=rank[p2[i]];
		if(b>maxn) maxn=b;
		for(j=a;j<=b;j++) col[j]=i;
	}
	ans=0;
	memset(can,0,sizeof can);
	for(i=1;i<=maxn;i++) if(col[i]!=0) can[col[i]]=true;
	for(i=1;i<=n;i++) if(can[i]) ans++;
	printf("%d\n",ans);
}

int main(){
	int i,j,k,t;
	scanf("%d",&t);
	for(i=1;i<=t;i++){
		init();
		process();
	}
	return 0;
}
