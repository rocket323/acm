#include <iostream>
using namespace std;

int N, ans, size, H[20010];

int pop(){
	int ans,i,j,k,t, tmp;
	ans=H[1];
	H[1]=H[size--];
	k=1;
	while(k<size){
		i=k*2; j=i+1;
		if(i>size) break;
		if(j>size) t=i;
		else{
			if(H[i]<H[j]) t=i;
			else t=j;
		}
		if(H[k]>H[t]){
			tmp=H[k]; H[k]=H[t]; H[t]=tmp;
			k=t;
		}
		else break;
	}
	return ans;
}

void push(int val){
	int i,j,k, mid, tmp;
	H[++size]=val;
	k=size;
	while(k>1){
		mid=k/2;
		if(H[k]<H[mid]){
			tmp=H[k]; H[k]=H[mid]; H[mid]=tmp;
			k=mid;
		}
		else break;
	}
}

void process(){
	int a, b,i,j,k, ans=0;
	while(size>0){
		a=pop();
		if(size==0) break;
		b=pop();
		push(a+b);
		ans+=(a+b);
	}
	printf("%d\n", ans);
}

int main(){
	int i,j,k;
//	freopen("plank.4.in", "r", stdin);
	scanf("%d", &N);
	size=0;
	for(i=0; i<N; ++i){
		scanf("%d", &k);
		push(k);
	}
	process();
//	while(1);
	return 0;
}
