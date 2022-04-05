#include <iostream>
#include <algorithm>
using namespace std;

struct Cow{
	int a, b;
}C[25001], B[25001];

bool cmp(const Cow& A, const Cow& B){
	return (A.a<B.a||(A.a==B.a&&A.b<B.b));
}

int N, T;

void process(){
	int i,j,k, last=0, pos=1, rec=0, cnt=0;
	int top=1;
//	sort(C, C+N, cmp);
	B[1]=C[0];
	for(i=1; i<N; ++i){
		if(C[i].b>B[top].b){
			B[++top]=C[i];
		}
	}
	while(1){
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
//	freopen("cleaning.8.in", "r", stdin);
//	freopen("cleaning.1.out", "w", stdout);
//	freopen("oo.out", "w", stdout);
	scanf("%d%d", &N, &T);
	for(i=0; i<T; ++i)
		scanf("%d%d", &C[i].a, &C[i].b);
	process();
//	while(1);
	return 0;
}
