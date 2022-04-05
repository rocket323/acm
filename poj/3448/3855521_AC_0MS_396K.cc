#include <iostream>
#define MaxL 100000000
using namespace std;

char S[500], T[500];
char res[500], tmp[500];
int val[500], len;
bool flag;

int getV(char ch){
	if(ch=='I') return 1;
	if(ch=='V') return 5;
	if(ch=='X') return 10;
	if(ch=='L') return 50;
	if(ch=='C') return 100;
	if(ch=='D') return 500;
	if(ch=='M') return 1000;
}

int getVal(char s[], int len){
	int i,j,k, p=0, a, b;
//	cout<<s<<endl;
	if('0'<=s[0]&&s[0]<='9'){
		i=0; p=0;
		while(s[i]){
			p=p*10+(s[i]-'0');
			i++;
		}
	//	cout<<p<<' '<<val[p]<<endl;
		if(val[p]==-1){
			flag=false;
			return (-MaxL);
		}
		else return val[p];
	}
	else{
		int ans=0; i=0;
		while(i<len){
			a=getV(s[i]);
			b=0;
			if(i<len-1) b=getV(s[i+1]);
			if(a<b){
				ans+=(b-a);
				i+=2;
			}
			else{
				ans+=a;
				i++;
			}
		}
		return ans;
	}
}


int getSum( ){
	int i,j,k, len=strlen(T);
	char tt[500]="";
	int sum=0;
	int pos=0;
//	cout<<val[1]<<endl;
	while(true){
		for(i=pos+1; i<len; i++)
			if(T[i]=='+'||T[i]=='-') break;
		i--;
		
		strcpy(tt, "");
		strncpy(tt, T+pos+1, i-pos);
		tt[i-pos]='\0';
		
		if(T[pos]=='+'){
			k=getVal(tt, strlen(tt));
		//	cout<<tt<<' '<<strlen(tt)<<endl;
		//	cout<<"A "<<k<<endl;
			sum+=k;
		}
		else{
			k=getVal(tt, strlen(tt));
	//	cout<<tt<<' '<<strlen(tt)<<endl;
		//	cout<<"B "<<k<<endl;
			sum-=k;
		}
		
		pos=i+1;
		if(pos==len) break;
	}
	return sum;
}

void getExpr(int num, int lv){
	int i,j,k;
	strcpy(tmp, "");
	if(lv==1){
		if(num<4) for(i=1; i<=num; i++) strcat(tmp,"I");
		else if(num==4) strcpy(tmp,"IV");
		else if(num<9){
			strcpy(tmp, "V");
			for(i=1; i<=(num-5); i++) strcat(tmp, "I");
		}
		else if(num==9) strcpy(tmp, "IX");
	}else
	if(lv==2){
		if(num<4) for(i=1; i<=num; i++) strcat(tmp,"X");
		else if(num==4) strcpy(tmp,"XL");
		else if(num<9){
			strcpy(tmp, "L");
			for(i=1; i<=(num-5); i++) strcat(tmp, "X");
		}
		else if(num==9) strcpy(tmp, "XC");
	}else
	if(lv==3){
		if(num<4) for(i=1; i<=num; i++) strcat(tmp,"C");
		else if(num==4) strcpy(tmp,"CD");
		else if(num<9){
			strcpy(tmp, "D");
			for(i=1; i<=(num-5); i++) strcat(tmp, "C");
		}
		else if(num==9) strcpy(tmp, "CM");
	}else
	if(lv==4){
		for(i=1; i<=num; i++) strcat(tmp,"M");
	}else
	if(lv==5){
		for(i=1; i<=10; i++) strcat(tmp, "M");
	}
}
	

void CtStr(int num){
	int i,j,k;
	int a[10], tp=0;
	strcpy(res, "");
	while(num>0){
		tp++;
		a[tp]=num%10;
		num=num/10;
	}
	for(i=tp;i>=1;i--)
		if(a[i]!=0){
			getExpr(a[i], i);
			strcat(res, tmp);
		}
}	


void fuZhi( ){
	int i,j,k, pos, p=0, ans=0;
	i=0; len=strlen(S);
	
	flag=true;
	while(S[i]!='='){
		p=p*10+(S[i]-'0');
		i++;
	}
	pos=i+1;
	if(S[pos]=='-'){
		strncpy(T, S+pos, len-pos);
		T[len-pos]='\0';
		ans=getSum( );
	}
	else{
		strncpy(T, S+pos, len-pos);
		T[len-pos]='\0';
		strcat(T, " ");
		for(i=len-pos; i>0; i--) T[i]=T[i-1];
		T[0]='+';
		ans=getSum( );
	}
	
	if(ans<0||ans>10000||!flag){
		printf("Error\n");
		return;
	}
//	cout<<p<<' '<<ans<<endl;
	val[p]=ans;
//	cout<<val[1]<<endl;
	CtStr(ans);
	printf("%d=%s\n", p, res);
//	printf("%d=%d\n", p, ans);

}

void process(){
	int i,j,k;
//	while(true){	
		if(strcmp(S, "QUIT")==0){
			printf("Bye\n");
			return;
		}
		if(strcmp(S, "RESET")==0){
			memset(val, -1, sizeof val);
			printf("Ready\n");
			return;
		}
	
		fuZhi( );
	//	gets(S);
//	}
	
//	cout<<val[1]<<endl;
}	

int main(){
	int i,j,k;
//	freopen("E.in", "r", stdin);
//	freopen("oo.out", "w", stdout);
	memset(val, -1, sizeof val);
	while(gets(S)){
	//	memset(val, -1, sizeof val);
		process();
	}
//	while(k=1);
	return 0;
}
