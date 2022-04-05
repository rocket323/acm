#include <iostream>
#include <algorithm>
using namespace std;

struct Cow{
	int fir, sec, idx;
}C[50001], CC[50001];

int N, K;

bool cmp1(Cow A, Cow B){
	return (A.fir>B.fir);
}

bool cmp2(Cow A, Cow B){
	return (A.sec>B.sec);
}

void init(){
	scanf("%d%d", &N, &K);
	for(int i=0; i<N; ++i){
		scanf("%d%d", &C[i].fir, &C[i].sec);
		C[i].idx=i+1;
	}
}
void process(){
	int i,j,k;
	sort(C, C+N, cmp1);
	for(i=0; i<K; ++i) CC[i]=C[i];
	sort(CC, CC+K, cmp2);
	printf("%d\n", CC[0].idx);
}

int main(){
//	freopen("3664.in", "r", stdin);
	init();
	process();
	return 0;
}