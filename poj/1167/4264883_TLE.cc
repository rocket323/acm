#include <iostream>
using namespace std;

int A[60], res, N, Max;
int line[18][300], cnt;
int s[18], it[18];

void init(){
	int i,j,k;
	
	memset(A, 0, sizeof A);
	memset(line, 0, sizeof line);
	
	for(i=1; i<=N; ++i){
		scanf("%d", &k);
		++A[k];
		Max = k;
	}
}

int checkin(int now, int a, int b){
	line[now][0] = 0;
	int i,j,k = a;

	line[now][++line[now][0]] = a;
	int save = a;
	a-=b;
	while(a>=0){
		if(A[a]==0) return 0;
		line[now][++line[now][0]] = a;
		a-=b;
	}
	a = save + b;
	while(a<60){
		if(A[a]==0) return 0;
		line[now][++line[now][0]] = a;
		a+=b;
	}
		
	return 1;
}

int update(int now, int add){
	int i,j,k, res = 0;
	for(i=1; i<=line[now][0]; ++i){
		A[line[now][i]]+=add;
		if(add==-1&&A[line[now][i]]>res) res = A[line[now][i]];
	}
	if(add==1)
		line[now][0] = 0;
	return res;
}

void dfs(int now, int cnt, int left){
	if(now+left>=res) return;
	int i,k=-1, Max = 0;
	for(i=0; i<=59; ++i)
		if(A[i]>Max){
			Max = A[i];
			k = i;
		}
	if(k==-1) return;
	
	for(i=1; i<60; ++i){
		
		if(checkin(now, k, i)){
			if(cnt-line[now][0]==0){
				res = now;
				update(now, 1);
				return;
			}
			else{
				int p = update(now, -1);
				dfs(now+1, cnt-line[now][0], p);
				update(now, 1);
			}
		}
		else line[now][0] = 0;
	}
}

void process(){
	int i,j,k;
	res = 17;
	dfs(1, N, 0);
	
	printf("%d\n", res);

}

int main(){
//	freopen("1167.in", "r", stdin);
//	while(scanf("%d", &N)!=EOF){
		scanf("%d", &N);
		init();
		process();
//	}
//	while(1);
	return 0;
}
