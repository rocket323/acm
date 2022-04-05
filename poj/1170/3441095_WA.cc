#include <iostream>
#define Max 10000000
using namespace std;

int c[6], num[6], p[6],pos[1001];
int sn[100][6], sp[100];
int b,stu,n,t;
int x,y;
int f[100][6][6][6][6][6];

void init(){
	int i,j,k;
	cin>>b;
	memset(num,0,sizeof num);
	memset(sn,0,sizeof sn);
	memset(p,0,sizeof p);
	memset(sp,0,sizeof sp);
	for(i=1;i<=b;i++){
		cin>>c[i]>>num[i]>>p[i];
		pos[c[i]]=i;
	}
	cin>>n;
	
	for(i=1;i<=n;i++){
		cin>>t;
		for(j=1;j<=t;j++){
			cin>>x>>y;
			sn[i][pos[x]]=y;
		}
		cin>>sp[i];
	}
}

void process(){
	int i,j,k,a1,a2,a3,a4,a5,x,ans=0;
	
	for(i=0;i<=n;i++)
		for(a1=0; a1<=num[1]; a1++)
			for(a2=0; a2<=num[2]; a2++)
				for(a3=0; a3<=num[3]; a3++)
					for(a4=0; a4<=num[4]; a4++)
						for(a5=0; a5<=num[5]; a5++){
							f[i][a1][a2][a3][a4][a5]=p[1]*a1+p[2]*a2+p[3]*a3+p[4]*a4+p[5]*a5;
						}
	f[0][0][0][0][0][0]=0;
	for(i=1;i<=b;i++) ans+=p[i]*num[i];
	for(i=1;i<=n;i++)
		for(a1=sn[i][1]; a1<=num[1]; a1++)
			for(a2=sn[i][2]; a2<=num[2]; a2++)
				for(a3=sn[i][3]; a3<=num[3]; a3++)
					for(a4=sn[i][4]; a4<=num[4]; a4++)
						for(a5=sn[i][5]; a5<=num[5]; a5++){
							f[i][a1][a2][a3][a4][a5]=f[i-1][a1][a2][a3][a4][a5];
							x=f[i-1][a1-sn[i][1]][a2-sn[i][2]][a3-sn[i][3]][a4-sn[i][4]][a5-sn[i][5]];
							if(x+sp[i]<f[i][a1][a2][a3][a4][a5])
								f[i][a1][a2][a3][a4][a5]=x+sp[i];
							x=f[i][a1][a2][a3][a4][a5]+(num[1]-a1)*p[1]+(num[2]-a2)*p[2]+(num[3]-a3)*p[3]+(num[4]-a4)*p[4]+(num[5]-a5)*p[5];
							if(x<ans){
								ans=x;
							}
						}
	cout<<ans<<endl;
	//cout<<f[2][3][2][0][0][0]<<endl;
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}
