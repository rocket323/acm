#include <iostream>
using namespace std;

int A[60], res, N, Max;
int line[18][300], cnt;
int s[18], it[18];

void init(){
	int i,j,k;
	
	memset(A, 0, sizeof A);
	memset(line, 0, sizeof line);
	res = 18;
	for(i=1; i<=N; ++i){
		scanf("%d", &k);
		++A[k];
		Max = k;
	}
}

int checkin(int now, int a, int b, int c){
	line[now][0] = 0;
	int i,j,k = a;
	for(k=a; k<=Max; k+=c){
		if(A[k]==0) return 0;
		line[now][++line[now][0]] = k;
		A[k]--;
	}
	return 1;
}

void checkout(int now, int a, int b, int c){
	int i,j,k;
	for(i=1; i<=line[now][0]; ++i){
		A[line[now][i]]++;
	}
	line[now][0] = 0;
}

void save(){
	int i,j,k;
	for(i=1; i<=res; ++i){
		s[i] = line[i][1];
		it[i] = line[i][2]-line[i][1];
	}
}

void dfs(int now, int cnt){
	if(now>=res) return;
	int i,k=-1;
	for(i=0; i<60; ++i)
		if(A[i]>0){ k = i; break; }
	if(k==-1) return;
	for(i=k+1; i<60; ++i){
		if(!A[i]) continue;
		if(checkin(now, k, i, i-k)){
			if(cnt-line[now][0]==0){ res = now; save(); break; }
			else dfs(now+1, cnt-line[now][0]);
		}
		checkout(now, k, i, i-k);
	}
}

void process(){
	int i,j,k;
	
	dfs(1, N);
	
//	printf("%d\n", res);
	for(i=1; i<=res; ++i){
		cout<<s[i]<<' '<<it[i]<<endl;
	}
	
}

int main(){
//	freopen("1167.in", "r", stdin);
	while(scanf("%d", &N)!=EOF){
		init();
		process();
	}
//	while(1);
	return 0;
}
