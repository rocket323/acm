#include <iostream>
using namespace std;

int N, pre[200], age[200], tp, ptr[200];
char S[200][100], name[200][100];
char mm[200][100], tmp[100];
int gg[200], tt;

int find(int now){
	if(pre[now]==now) return now;
	int ans=find(pre[now]);
	age[now]=age[pre[now]]+age[now];
	pre[now]=ans;
	return ans;
}

int getID(char s[]){
	for(int i=1; i<=tp; i++){
		if(strcmp(S[i], s)==0){
		//	cout<<"here"<<endl;
			return i;
		}
	}
	tp++;
	strcpy(S[tp], s);
	return tp;
}

void process(int tes){
	int i,j,k, a, b, x, y;
	char f[100], c[100];
	
	
	cin>>N;
	
	tp=1;
	strcpy(S[1], "Ted");
	
	for(i=1; i<200; i++){ pre[i]=i; age[i]=0; }
	
	
	for(i=1; i<=N; i++){
		cin>>f>>c>>k;
		a=getID(f); b=getID(c);
		x=find(a); y=find(b);
		pre[y]=a;
		age[y]=-k-age[b];
	//	cout<<f<<' '<<c<<endl;
		strcpy(mm[b], c);
		
	}
	for(i=2; i<=tp; i++){
		k=find(i);
		gg[i]=100+age[i];
	}
	for(i=2; i<tp; i++)
		for(j=i+1; j<=tp; j++)
			if(gg[i]<gg[j]||(gg[i]==gg[j]&&strcmp(mm[i], mm[j])>0)){
				strcpy(tmp, mm[i]);
				strcpy(mm[i], mm[j]);
				strcpy(mm[j], tmp);
				tt=gg[i]; gg[i]=gg[j]; gg[j]=tt;
			}
	printf("DATASET %d\n", tes); 
	for(i=2; i<=tp; i++){
		cout<<mm[i]<<' '<<gg[i]<<endl;
	}
				
	//	cout<<getID("Ted")<<endl;
	
}

int main(){
	int i,j,k, T;
//	freopen("2021.in", "r", stdin);
	cin>>T;
	for(i=1; i<=T; ++i){
		process(i);
	}
//	while(k=1);
	return 0;
}
