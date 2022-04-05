#include <iostream>
using namespace std;

int f[15], g[15];

int main(){
	int i,j,k;
	g[1]=1;
	for(i=2; i<=12; i++) g[i]=2*g[i-1]+1;
	f[1]=1;
	for(i=2; i<=12; i++){
		f[i]=10000000;
		for(j=1; j<i; j++)
			if(2*f[i-j]+g[j]<f[i])
				f[i]=2*f[i-j]+g[j];
	}
	for(i=1; i<=12; i++) cout<<f[i]<<endl;
//	while(k=1);
	return 0;
}
