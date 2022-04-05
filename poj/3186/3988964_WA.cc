#include <iostream>
using namespace std;

int N, ans, A[2001], B[2001];

int compare(int p1, int p2){
	while(p1<=N&&p2<=N){
		if(A[p1]>B[p2]) return 1;
		else if(A[p1]<B[p2]) return -1;
		else {
			p1++; p2++;
		}
	}
	if(p1<=N) return 1;
	else return -1;
}

void process(){
	int i,j,k, cnt=1, p1=1, p2=1, ans=0;
	for(i=1; i<=N; ++i)
		B[i]=A[N+1-i];
	
	for(i=1; i<=N; ++i){
		if(compare(p1, p2)<0){
			ans+=i*A[p1];
			p1++;
		}
		else {
			ans+=i*B[p2];
			p2++;
		}
	}
	printf("%d\n", ans);
}

int main(){
	scanf("%d", &N);
	for(int i=1; i<=N; i++) scanf("%d", &A[i]);
	ans=0;
	process();
	return 0;
}
