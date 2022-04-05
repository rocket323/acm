#include <iostream>
using namespace std;


int N, cu[101];

void init(){
	int i;
	for(i=0;i<=100;i++)
		cu[i]=i*i*i;
}

void process(){
	int a,b,c,d;
	for(a=2;a<=N;a++)
		for(b=2;b<=N;b++)
			for(c=b;c<=N;c++)
				for(d=c;d<=N;d++)
					if(cu[a]==cu[b]+cu[c]+cu[d])
						printf("Cube = %d, Triple = (%d,%d,%d)\n",a,b,c,d);
}

int main(){
	int i,j,k;
//	freopen("1543.in","r",stdin);
	scanf("%d",&N);
	init();
	process();
//	while(k=1);
	return 0;
}
