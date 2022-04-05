#include <iostream>
#define MaxL 10000000
using namespace std;

int N, br[101][101], p[101][101], nex[101];

void init(){
	int i,j,k;
	scanf("%d",&N);
	for(i=1;i<=N;i++){
		scanf("%d",&nex[i]);
		for(j=1;j<=nex[i];j++){
			scanf("%d%d",&br[i][j], &p[i][j]);
		//	cout<<br[i][j]<<' '<<p[i][j]<<endl;
		}
	}
}

void process(){
	int i,j,k, a, b, Min, Minb, sum, num;
	double ans=0.0;
	for(a=1;a<=N;a++)
		for(b=1;b<=nex[a];b++){
			Minb=br[a][b];
			sum=p[a][b]; num=1;
			for(i=1;i<=N;i++){
				if(i==a) continue;
				Min=MaxL;
				for(j=1;j<=nex[i];j++)
					if(br[i][j]>=Minb&&p[i][j]<Min){
						Min=p[i][j];
					}
				if(Min!=MaxL){
					sum+=Min;
					num++;
				}
			}
			if(num==N&&(Minb+0.0)/sum>ans){
				ans=(Minb+0.0)/sum;
			}
		}
	printf("%.3f\n",ans);
}

int main(){
	int i,j,k;
//	freopen("1018.in","r",stdin);
	scanf("%d",&k);
	for(i=1;i<=k;i++){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
