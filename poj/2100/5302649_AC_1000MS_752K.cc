#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;
const int T=6;
const int N=2;
int data[T][N];

int main(){
int i,sum,k,bound,r;
__int64 n,add,sub,c;
    while(scanf("%I64d",&n)!=EOF){
  sum=0;
  int s[T]={0};
  bound=1.5*pow(n,1.0/3);  //r-k的最值
  for(sub=bound;sub>=1;sub--){ //枚举r-k的范围
      //  (r-k)[ 3(r+k)^2 + (r-k)^2 + 6(r+k) + 2 ] = 12*n
   if(12*n%sub!=0) continue;
   c=sub*sub-12*n/sub+2;
   add=(-6+sqrt(36.0-12*c))/6;
   if(3*add*add+6*add + c !=0) continue;
   if((add+sub)%2!=0 || (add-sub)%2!=0) continue;
   r=(add+sub)/2;
   k=(add-sub)/2;
   if(k<0||r<=k) continue;
   data[sum][0]=k;
   data[sum][1]=r;
   sum++;
  }
  printf("%d\n",sum);
  if(sum==0)  continue;
        for(k=0;k<sum;k++){
   printf("%d",data[k][1] - data[k][0]);
  for(i=data[k][0]+1;i<=data[k][1];i++){
      printf(" %d",i);
  }
  putchar('\n');
  }  
}
return 0;
} 

