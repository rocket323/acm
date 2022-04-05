#include <iostream>
using namespace std;

char S[7];
int N, A[200], B[200], C[200], point;

void out2(int B[]){
	int i;
	for(i=B[0]; i>=1; --i) cout<<B[i];
	cout<<endl;
}

void out(int B[]){
	int i,k, en;
	point--;
	point*=N;
	if(point<B[0]){
		k=B[0]-point; i=B[0];
		while(k>0){
			cout<<B[i]; k--;
			i--;
		}
		
		en=1;
		while(B[en]==0) en++;
		if(en<point) cout<<'.';
		for(i=point; i>=en; --i) cout<<B[i];
		cout<<endl;
	}
	else{
		
		for(i=1; i<=point-B[0]; ++i) cout<<'0';
		en-1;
		while(B[en]==0) en++;
		if(en<point) cout<<'.';
		for(i=B[0]; i>=1; --i) cout<<B[i];
		cout<<endl;
	}
}

void init(){
	int i,j,k=1;
	A[0]=0;
	for(i=strlen(S)-1; i>=0; --i){
		if(S[i]=='.'){
			point=k;
			--k;
		}
		else{
			A[k]=S[i]-'0';
			A[0]++;
		}
		++k;
	}
	B[0]=A[0];
	for(i=1; i<=A[0]; ++i) B[i]=A[i];
}

void Multiple(int B[], int A[], int C[], int tt){
	int i,j,k, l1, l2, l;
	for(i=0; i<200; ++i) C[i]=0;
	for(i=1; i<=A[0]; ++i)
		for(j=1; j<=B[0]; ++j){
			k=A[i]*B[j];
			C[i+j-1]+=k;
			C[i+j]+=C[i+j-1]/10;
			C[i+j-1]=C[i+j-1]%10;
		}
	C[0]=199; 
	while(C[C[0]]==0) C[0]--;
	B[0]=C[0];
	for(i=1; i<=C[0]; ++i) B[i]=C[i];
}

void process(){
	int i,j,k;
	for(i=2; i<=N; ++i){
		Multiple(B, A, C, i);
	}
	out(B);
}

int main(){
//	freopen("1001.in", "r", stdin);
//	freopen("1001.out", "w", stdout);
	while(scanf("%s%d", S, &N)!=EOF){
		init();
		process();
	}
//	while(1);
	return 0;
}
