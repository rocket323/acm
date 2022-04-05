#include <iostream>
#include <cmath>
using namespace std;

int N, factor, ans;

bool isPrime(int num){
	int k=sqrt(num);
	for(int i=2; i<=k; ++i)
		if(num%i==0) return 0;
	return 1;
}

int Max(int a, int b){
	return (a>b)?a:b;
}

int fun(int num){
	int k=sqrt(num), ans=0, p;
	for(int i=1; i<=k; ++i)
		if(num%i==0){
			p=num/i;
			if(isPrime(p)) ans=Max(ans, p);
			if(isPrime(i)) ans=Max(ans, i);
		}
	return ans;
}

void process(){
	int i,j,k;
	factor=-10000;
	scanf("%d", &N);
	for(i=1; i<=N; ++i){
		scanf("%d", &k);
		if((j=fun(k))>factor){
			factor=j;
			ans=k;
		}
	}
	printf("%d\n", ans);
}

int main(){
//	freopen("3048.in", "r", stdin);
	process();
//	while(1);
	return 0;
}
