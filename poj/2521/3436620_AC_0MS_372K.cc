#include <iostream>
using namespace std;

int main(){
	int n,m,p,c,k;
	scanf("%d%d%d%d",&n,&m,&p,&c);
	while(true){
		if(n==0&&m==0&&p==0&&c==0) break;
		printf("%d\n",n-m+p);
		scanf("%d%d%d%d",&n,&m,&p,&c);
	}
	return 0;
}
