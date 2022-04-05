#include <iostream>
using namespace std;
int main(){
	double a,ans=0;
	int i,j,k;
	for(i=1;i<=12;i++){
		cin>>a;
		ans+=a;
	}
	ans=ans/12.0;
	printf("$%.2f\n",ans);
	return 0;
}
