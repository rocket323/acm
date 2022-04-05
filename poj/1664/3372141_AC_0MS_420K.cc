#include <iostream>
using namespace std;

int tot,m,k;

void process(int step,int app,int start){
	int i;
	if(step==(k+1)&&app==0){
		tot++;
		return;
	}
	if(step>k) return;
	for(i=start;i<=m;i++){
		process(step+1,app-i,i);
	}
}
int main(){
	int t,i,j;
	cin>>t;
	for(i=1;i<=t;i++){
		tot=0;
		cin>>m>>k;
		process(1,m,0);
		cout<<tot<<endl;
	}
	return 0;
}
