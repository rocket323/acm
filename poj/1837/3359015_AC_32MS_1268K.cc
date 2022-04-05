#include <iostream>
using namespace std;

int ld[21][7501]={0},rd[21][7501]={0},n,c,g,a[50],w[50];
int main(){
	int i,j,k,t,m,n;
	//freopen("1837.in","r",stdin);
	cin>>c>>g;
	for(i=1;i<=c;i++) cin>>a[i];
	for(i=1;i<=g;i++) cin>>w[i];
	ld[0][0]=1; rd[0][0]=1;
	for(i=1;i<=g;i++)
		for(j=-7500;j<=7500;j++){
			if(j<0&&ld[i-1][-1*j]>0){
				for(k=1;k<=c;k++){
					t=j+w[i]*a[k];
					if(t>=-7500&&t<0){
						ld[i][-1*t]+=ld[i-1][-1*j];
					}
					if(t<=7500&&t>=0){
						rd[i][t]+=ld[i-1][-1*j];
					}
				}
			}
			if(j>=0&&rd[i-1][j]>0){
				for(k=1;k<=c;k++){
					t=j+w[i]*a[k];
					if(t>=-7500&&t<0){
						ld[i][-1*t]+=rd[i-1][j];
					}
					if(t<=7500&&t>=0){
						rd[i][t]+=rd[i-1][j];
					}
				}
			}
		}
	cout<<rd[g][0]<<endl;
	//while(k=1);
	return 0;
}
