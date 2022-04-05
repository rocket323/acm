#include <iostream>
using namespace std;

int N, T, D, U, F;

int main(){
	int i,j,k, ans=0, sum=0, a, b;
//	freopen("3672.in", "r", stdin);
	char ch;
	scanf("%d%d%d%d%d\n", &T, &N, &U, &F, &D);
	for(i=1; i<=N; ++i){
		scanf("%c\n", &ch);
		if(ch=='f'){
			a=b=F;
		}
		else {
			a=U; b=D;
		}
		sum+=(a+b);
		if(sum<=T) ans=i;
		else break;
	}
	printf("%d\n", ans);
//	while(1);
	return 0;
}
