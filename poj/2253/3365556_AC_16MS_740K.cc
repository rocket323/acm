#include <iostream>
#include <cmath>
#define MaxL 100000000
using namespace std;

int n,m,x[201],y[201],cnt=0;
double w[201][201],dist[201];
bool used[201]={0};

void init(){
	int i,j,k;
	for(i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			w[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

double maxM(double a, double b){
	if(a>b) return a;
	return b;
}

void process(){
	int x,i,j,k;
	double min,t;
	for(i=1;i<=n;i++) dist[i]=MaxL;
	dist[1]=0;
	memset(used,0,sizeof used);
	for(x=1;x<=n;x++){
		min=MaxL;
		for(i=1;i<=n;i++)
			if(dist[i]<min&&!used[i]){
				min=dist[i];
				k=i;
			}
		used[k]=true;
		for(i=1;i<=n;i++){
			t=maxM(dist[k],w[k][i]);
			if(t<dist[i])
				dist[i]=t;
		}
	}
	printf("Scenario #%d\n",cnt);
	printf("Frog Distance = %.3f\n",dist[2]);
}

int main(){
	int k;
	cin>>n;
	while(n!=0){
		cnt++;
		init();
		process();
		cout<<endl;
		cin>>n;
	}
	return 0;
}
