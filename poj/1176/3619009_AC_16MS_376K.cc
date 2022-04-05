#include<iostream>
using namespace std;

int N,C,req[101], A[101];
int l[5],tp;
char S[20][150];

void init(){
	int i,j,k,a,b;
	scanf("%d%d",&N,&C);
	memset(req,-1,sizeof req);
	scanf("%d",&a);
	while(a!=-1){
		req[a]=1;
		scanf("%d",&a);
	}
	scanf("%d",&a);
	while(a!=-1){
		req[a]=0;
		scanf("%d",&a);
	}
	
	tp=0;
	
}

void addPlan(){
	int i,j,k;
	char tmp[150]="";
	tp++;
	for(i=1;i<=N;i++){
		if(A[i]==0) strcat(tmp,"0");
		else strcat(tmp,"1");
	}
	strcpy(S[tp], tmp);
}

void creatPlan(){
	int i,j,k;
	for(i=1;i<=N;i++) A[i]=1;
	if(l[1]){
		for(i=1;i<=N;i++)
			A[i]=1-A[i];
	}
	if(l[2]){
		for(i=1;i<=N;i++)
			if(i%2==1)
				A[i]=1-A[i];
	}
	if(l[3]){
		for(i=1;i<=N;i++)
			if(i%2==0)
				A[i]=1-A[i];
	}
	if(l[4]){
		for(i=0;i<=N;i++){
			k=3*i+1;
			if(k<=N)
				A[k]=1-A[k];
		}
	}
	for(i=1;i<=N;i++)
		if(req[i]!=-1&&req[i]!=A[i])
			return;
	addPlan();
}

void sort(){
	int i,j;
	char tmp[150];
	for(i=1;i<tp;i++)
		for(j=i+1;j<=tp;j++)
			if(strcmp(S[i], S[j])>0){
				strcpy(tmp, S[i]);
				strcpy(S[i], S[j]);
				strcpy(S[j], tmp);
			}
}

void out(){
	int i,j,k;
	for(i=1;i<=tp;i++)
		printf("%s\n",S[i]);
}				

void process(){
	int i,j,k, sum=0;
	for(l[1]=0;l[1]<=1;l[1]++)
		for(l[2]=0;l[2]<=1;l[2]++)
			for(l[3]=0;l[3]<=1;l[3]++)
				for(l[4]=0;l[4]<=1;l[4]++){
					sum=l[1]+l[2]+l[3]+l[4];
					if(C>=sum&&(C-sum)%2==0){
						creatPlan();
					}
				}
	sort();
	out();
}

int main(){
	int i,j,k;
//	freopen("1176.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
