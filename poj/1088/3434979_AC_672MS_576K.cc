#include <iostream>
#include <cmath>
using namespace std;

int n,m,h[101][101],tp=0,a[10001],r[10001],c[10001];
int f[10001];

void init(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++){
			tp++;
			scanf("%d",&h[i][j]);
			a[tp]=h[i][j];
			r[tp]=i;
			c[tp]=j;
		}
}

void qsort(int s, int t){
	int x=a[(s+t)/2];
	int i=s; int j=t;
	int tmp;
	while(i<j){
		while(a[i]<x) i++;
		while(a[j]>x) j--;
		if(i<=j){
			tmp=a[i]; a[i]=a[j]; a[j]=tmp;
			tmp=r[i]; r[i]=r[j]; r[j]=tmp;
			tmp=c[i]; c[i]=c[j]; c[j]=tmp;
			i++; j--;
		}
	}
	if(i<t) qsort(i,t);
	if(s<j) qsort(s,j);
}

bool adj(int s, int t){
	if(r[s]==r[t]&&abs(c[s]-c[t])==1) return true;
	if(c[s]==c[t]&&abs(r[s]-r[t])==1) return true;
	return false;
}

void process(){
	int i,j,k,ans=1;
	f[1]=1;
	for(i=2;i<=tp;i++){
		f[i]=1;
		for(j=1;j<i;j++)
			if(adj(i,j)&&a[j]<a[i]&&f[j]+1>f[i])
				f[i]=f[j]+1;
		if(f[i]>ans) ans=f[i];
	}
	printf("%d\n",ans);
}

int main(){
	int i,j,k;
	init();
	qsort(1,tp);
	process();
	return 0;
}
