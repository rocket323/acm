#include <iostream>
using namespace std;

int N, num, cr, cc;
int A[21][21];

void process(){
    int i,j,k;
    cr=cc=1;
    while(cc<=N){
        A[cr][cc]=num;
        cr++; num++;
        if(num>9) num=1;
        if(cr>cc){
            cc++; cr=1;
        }
    }
    for(i=1; i<=N; ++i){
        for(j=1; j<i; ++j) cout<<"  ";
        for(j=i; j<N; ++j) cout<<A[i][j]<<' ';
        cout<<A[i][N]<<endl;
    }
}

int main(){
    int i,j,k;
    cin>>N>>num;
    process();
    return 0;
}