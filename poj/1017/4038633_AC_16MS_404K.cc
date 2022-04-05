#include <iostream>
using namespace std;

int A[7], ans;

void go3(){
	ans++;
	if(A[3]==1){
		if(A[2]>=5){
			A[2]-=5;
			A[1]-=7;
		}
		else{
			if(A[2]<0) A[2]=0;
			A[1]-=(27-4*A[2]);
			A[2]=0;
		}
	}
	else if(A[3]==2){
		if(A[2]>=3){
			A[2]-=3;
			A[1]-=6;
		}
		else {
			if(A[2]<0) A[2]=0;
			A[1]-=(18-4*A[2]);
			A[2]=0;
		}
	}
	else if(A[3]==3){
		if(A[2]>=1){
			A[2]-=1;
			A[1]-=5;
		}
		else {
			A[2]=0;
			A[1]-=9;
		}
	}
}

void out(){
	for(int i=1; i<6; ++i) cout<<A[i]<<' ';
	cout<<A[6]<<endl;
}

void process(){
	int i,j,k;
	ans=A[6]; A[6]=0;
	
	//process 5*5
	ans+=A[5];
	A[1]-=11*A[5];
		
	//process 4*4
	ans+=A[4];
	if(A[2]<=0){
		A[1]-=20*A[4];	
	}
	else if(5*A[4]>=A[2]){
		
		A[1]-=4*(5*A[4]-A[2]);
		A[2]=0;
	}
	else{
		A[2]-=5*A[4];
	}
	
	//process 3*3
	ans+=(A[3]/4);
	A[3]=A[3]%4;
	if(A[3]>0) go3();
	
	//process 2*2
	if(A[2]>0){
		ans+=A[2]/9;
		A[2]%=9;
		if(A[2]>0){
			ans++;
			A[1]-=(36-A[2]*4);
		}	
	}
	
	//process 1*1
	if(A[1]>0){
		ans+=(A[1]/36);
		A[1]%=36;
		if(A[1]>0)
			ans++;
	}
	printf("%d\n", ans);
}

int main(){
	int i, sum=0, k=0;
	for(i=1; i<=6; ++i){
		scanf("%d", &A[i]);
		sum+=A[i];
	}
	while(sum!=0){
		process();
		sum=0;
		for(i=1; i<=6; ++i){
			scanf("%d", &A[i]);
			sum+=A[i];
		}
	}
	return 0;
}
