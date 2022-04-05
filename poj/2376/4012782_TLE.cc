#include <iostream>
#include <algorithm>
using namespace std;

struct Cow{
	int a, b;
}C[25001];

bool cmp(Cow A, Cow B){
	return (A.b<B.b);
}

int N, T;

void process(){
	int i,j,k, last=1, pos=0, rec=0, cnt=0;
	sort(C, C+N, cmp);

	while(1){
		rec=-1;
		while(pos<N){
			if(C[pos].a<=last&&pos>rec) rec=pos;
			pos++;
		}
		if(rec==-1){
		//	printf("-1\n");
			return;
		}
		last=C[rec].b;
		pos=rec+1; cnt++;
		if(pos==N){
			printf("%d\n", cnt);
			return;
		}
	}
}

int main(){
	int i,j,k;
//	freopen("2376.in", "r", stdin);
	scanf("%d%d", &N, &T);
	for(i=0; i<T; ++i)
		scanf("%d%d", &C[i].a, &C[i].b);
	process();
//	while(1);
	return 0;
}
