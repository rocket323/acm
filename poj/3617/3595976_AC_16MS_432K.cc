#include <iostream>
using namespace std;

int N,tp;
char A[30003],T[30003];

void init(){
	int i,j,k;
	cin>>N;
	for(i=1;i<=N;i++){
		cin>>A[i];
	}
}

void process(){
	int i,j,k,ti,tj;
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
			ti=i+1; tj=j-1;
			while(ti<tj&&A[ti]==A[tj]){
				ti++; tj--;
			}
			if(ti>tj){
				tp++;
				T[tp]=A[i];
				i++;
			}
			else{
				if(A[ti]<A[tj]){
					tp++;
					T[tp]=A[i];
					i++;
				}
				else{
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
