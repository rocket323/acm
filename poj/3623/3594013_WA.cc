#include <iostream>
using namespace std;

int N;
char A[30003];

void init(){
	int i,j,k;
	scanf("%d",&N);
	for(i=1;i<=N;i++)
		cin>>("%d",&A[i]);
}

void process(){
	int i,j,k;
	i=1; j=N;
	while(i<=j){
		if(A[i]<A[j]){
			printf("%c",A[i]);
			i++;
		}
		else if(A[i]>A[j]){
			printf("%c",A[j]);
			j--;
		}
		else{
			if(j-i<=1){
				for(k=i;k<=j;k++)	
					printf("%c",A[k]);
				i++; j--;
			}
			else{
				if(A[i+1]<=A[j-1]){
					printf("%c",A[i]);
					i++;
				}
				else{
					printf("%c",A[j]);
					j--;
				}
			}
		}
	}
	printf("\n");
}

int main(){
	int i,j,k;
//	freopen("3623.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
