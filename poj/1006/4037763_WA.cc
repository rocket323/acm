#include <iostream>
using namespace std;

int a, b, c, d;

bool check(int cc){
	int i,j,k;
//	if(cc<a||cc<b||cc<c) return false;
	if( (cc-a)%23!=0 ) return false;
	if( (cc-b)%28!=0 ) return false;
	if( (cc-c)%33!=0 ) return false;
	return true;
}

void process(int tes){
	int i,j,k;
	printf("Case %d: ", tes);
	for(i=d+1; i<=21252; ++i){
		if(check(i)) break;
	}
	printf("the next triple peak occurs in %d days.\n", i-d);
}

int main(){
	int k=0;
//	freopen("1006.in", "r", stdin);
	scanf("%d%d%d%d", &a, &b, &c, &d);
	while(!(a==-1&&b==-1&&c==-1&&d==-1)){
		process(++k);
		scanf("%d%d%d%d", &a, &b, &c, &d);
	}
//	while(1);
	return 0;
}
