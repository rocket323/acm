#include <iostream>
using namespace std;

int n,sum,ave,a[65],finish=0;
bool used[65];

void init(){
	int i,j,k;
	sum=0;
	for(i=1;i<=n;i++) { cin>>a[i]; sum+=a[i]; }
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
			if(a[i]<a[j]){
				k=a[i]; a[i]=a[j]; a[j]=k;
			}
}

bool s(int);

bool search(int board,int start, int curlen){
	if(board==finish) return true;
	if(curlen==0) return s(board+1);
	if(start>n) return false;
	if(curlen<0) return false;
	
	int i;
	for(i=start;i<=n;i++)
		if(!used[i]){
			used[i]=true;
			if(search(board,i+1,curlen-a[i])) return true;
			used[i]=false;
			if(a[i]==curlen) return false;
			else if(a[i]<curlen){
				i++;
				while(a[i]==a[i-1]) i++;
			}
		}
	return false;
}

bool s(int x){
	int i,j,k;
	for(i=1;i<=n;i++)
		if(!used[i]){
		
			used[i]=true;
			if(search(x,i+1,ave-a[i])) return true; 
			used[i]=false;
			//if(x==1){
			///	cout<<x<<' '<<i<<endl;
			//}
			//if(x==1) return false;
		}
	return false;
}

int process(){
	int i,j,k;
	for(i=a[1];i<=sum;i++){
		if(sum%i==0){
			memset(used,0,sizeof used);
			ave=i; finish=sum/i;
			if(s(1))
				return ave;
		}
	}
}

int main(){
	int i,j,k;
	//freopen("1011.in","r",stdin);
	cin>>n;
	while(n!=0){
		init();
		k=process();
		cout<<k<<endl;
		cin>>n;
	}
	//cout<<"end."<<endl;
	//while(k=1);
	return 0;
}
