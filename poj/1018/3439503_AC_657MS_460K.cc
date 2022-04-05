#include <iostream>
#define Max 100000000
using namespace std;

int n,m,p[101][101],b[101][101],l[101];

void init(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&l[i]);
		for(j=1;j<=l[i];j++)
			scanf("%d%d",&b[i][j],&p[i][j]);
	}
}

void process(){
	int i,j,k,x,aa,bb,num,min,sum;
	double ans=0.0;
	for(aa=1;aa<=n;aa++)
		for(bb=1;bb<=l[aa];bb++){
			x=b[aa][bb]; num=0; sum=0;
			for(i=1;i<=n;i++){
				min=Max; 
				for(j=1;j<=l[i];j++)
					if(b[i][j]>=x&&p[i][j]<min){
						min=p[i][j];
					}
				if(min!=Max) num++;
				sum+=min;
			}
			if(num==n&&(x+0.0)/sum>ans){
				ans=(x+0.0)/sum;
			}
		}
	printf("%.3f\n",ans);
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
