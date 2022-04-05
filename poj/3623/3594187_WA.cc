#include <iostream>
using namespace std;

int N,tp;
char A[30003],T[30003];

void init(){
	int i,j,k;
	scanf("%d",&N); k=0;
	for(i=1;i<=N;i++){
		cin>>("%d",&A[i]);
	//	cout<<(++k)<<' '<<A[i]<<endl;
	}
}

void process(){
	int i,j,k;
	i=1; j=N;
	while(i<=j){
		if(A[i]<A[j]){
			//printf("%c",A[i]);
			tp++;
			T[tp]=A[i];
			i++;
		}
		else if(A[i]>A[j]){
		//	printf("%c",A[j]);
			tp++;
			T[tp]=A[j];
			j--;
		}
		else{
			if(j-i<=1){
				for(k=i;k<=j;k++){
		//			printf("%c",A[k]);
					tp++;
					T[tp]=A[k];
				}
				i++; j--;
			}
			else{
				if(A[i+1]<=A[j-1]){
		//			printf("%c",A[i]);
					tp++;
					T[tp]=A[i];
					i++;
				}
				else{
		//			printf("%c",A[j]);
					tp++;
					T[tp]=A[j];
					j--;
				}
			}
		}
	}
	for(i=1;i<=tp;i++){
		printf("%c",T[i]);
			if(i%80==0)
				printf("\n");
	}
}

int main(){
	int i,j,k;
	tp=0;
//	freopen("3623.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
