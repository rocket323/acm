#include <iostream>
using namespace std; 

int sum,mid,num[7],b[430000],c[430000];
bool can[430000];

void dp(){
	int i,j,k,t,tmp;
	memset(can,0,sizeof can);
	memset(b,0,sizeof b);
	memset(c,0,sizeof c);
	can[0]=1;
	t=0;
	for(i=1;i<=6;i++){
		t+=num[i]*i;
		if(t>mid) t=mid;
		for(j=i;j<=t;j++){
			if(can[j]) continue;
			tmp=j-i;
			if(can[tmp]){
				if(b[tmp]==i&&c[tmp]<num[i]){
					b[j]=i;
					c[j]=c[tmp]+1;
					can[j]=true;
				}
				else if(b[tmp]!=i&&num[i]>0){
					b[j]=i;
					c[j]=1;
					can[j]=true;
				}
			}
		}
	}
}

int main(){
	int i,j,k,test=0;
	sum=0;
	while(true){
		for(i=1;i<=6;i++){
			cin>>num[i];
			sum+=i*num[i];
		}
		if(sum==0) break;
		test++;
		if(sum%2==1){
			sum=0;
			printf("Collection #%d:\n",test);
			printf("Can't be divided.\n\n");
			continue;
		}
		mid=sum/2;
		dp();
		if(can[mid]){
			printf("Collection #%d:\n",test);
			printf("Can be divided.\n\n");
		}
		else {
			printf("Collection #%d:\n",test);
			printf("Can't be divided.\n\n");
		}
		sum=0;
	}
	return 0;
}
