#include <iostream>
#include <algorithm>
using namespace std;

struct Cow{
	int a, b;
}C[25001], B[25001];
int p[25001];

bool cmp(const int& i, const int& j){
	return (C[i].a<C[j].a||(C[i].a==C[j].a&&C[i].b<C[j].b));
}

int N, T;


void process(){
	int i,j,k, last=0, pos=1, rec=0, cnt=0;
	int top=1;
	for(i=0; i<N; ++i) p[i]=i;
	sort(p, p+N, cmp);
	B[1]=C[p[0]];
	for(i=1; i<N; ++i){
		if(C[p[i]].b>B[top].b){
			B[++top]=C[p[i]];
		}
	}
	
	while(pos<=top){
		rec=-1;
		while(pos<=top){
			if(B[pos].a<=last+1) rec=pos;
			else break;
			pos++;
		}
		if(rec==-1){
			printf("-1\n");
			return;
		}
		last=B[rec].b; pos=rec+1;
		cnt++;
		if(last>=T) break;
		
		if(pos>top) break;
	}
	if(last<T) printf("-1\n");
	else printf("%d\n", cnt);
}

int main(){
	int i,j,k;
	scanf("%d%d", &N, &T);
	for(i=0; i<N; ++i)
		scanf("%d%d", &C[i].a, &C[i].b);
	process();
	return 0;
}
