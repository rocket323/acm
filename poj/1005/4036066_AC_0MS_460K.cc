#include <cmath>
#include <iostream>
using namespace std;

double x, y, len;
const double pi=3.14159265358;

void process(int tes){
	int i,j,k, area=0;
	double R;
	cin>>x>>y;
	len=sqrt(x*x+y*y);
	for(i=1; ; ++i){
		area+=100;
		R=sqrt(area/pi);
		if(R>=len){
			printf("Property %d: This property will begin eroding in year %d.\n", tes, i);
			return;
		}
	}
}
	
int main(){
	int i, j, k, T;
//	freopen("1005.in", "r", stdin);
	scanf("%d", &T);
	for(i=1; i<=T; ++i){
		process(i);
	}
	printf("END OF OUTPUT.\n");
//	while(1);
	return 0;
}
