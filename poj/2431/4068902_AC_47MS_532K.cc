#include <iostream>
#include <algorithm>
#define MaxL 10000000
using namespace std;

struct station{
	int dist, dep;
}E[10004];

int N, cpos, cful, len;
int H[30010];

bool cmp(station A, station B){
	return A.dist>B.dist;
}

void init(){
	int i,j,k;
	scanf("%d", &N);
	for(i=0; i<=N; ++i){
		scanf("%d%d", &E[i].dist, &E[i].dep);
		if(i==N) k=E[i].dist;
	}
	E[N+1].dist=0; E[N+1].dep=MaxL;
	N+=2;
	sort(E, E+N, cmp);
	for(i=0; i<N; ++i)
		if(E[i].dist==k){
			cpos=i;
			cful=E[i].dep;
			break;
		}
}

int pop(){
	int ans=H[1];
	H[1]=H[len--];
	int k=1, i, j, t, tmp;
	while(k<len){
		i=2*k; j=i+1;
		if(i>len) break;
		if(j>len) t=i;
		else {
			if(H[i]>H[j]) t=i; 
			else t=j;
		}
		if(H[t]>H[k]){
			tmp=H[t]; H[t]=H[k]; H[k]=tmp;
			k=t;
		}
		else break;
	}
	return ans;
}

void push(int x){
	H[++len]=x;
	int mid, k, tmp;
	k=len;
	while(k>1){
		mid=k/2;
		if(H[k]>H[mid]){
			tmp=H[k]; H[k]=H[mid]; H[mid]=tmp;
			k=mid;
		}
		else break;
	}
}

int process(){
	int i;
	int stop=0, dist;
	int Max=-MaxL, rec=-1;
	len=0;
	while(1){
		for(i=cpos+1; E[0].dist-E[i].dist<=cful&&i<N; ++i) push(E[i].dep);
		if(i==N) return stop;
		while(E[0].dist-E[i].dist>cful){
			if(len==0) return -1;
			cful+=pop();
			stop++;
		}
		push(E[i].dep);
		cpos=i;
	}
	return -1;
}

int main(){
	init();
	cout<<process()<<endl;
	return 0;
}
