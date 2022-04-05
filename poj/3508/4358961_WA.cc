#include <iostream>
using namespace std;

int N;

int fun(int N){
    int ans = 0;
    while(N){
        ans++;
        N /= 10;
    }
    return ans;
}

int mi(int b){
    int res = 1;
    for(int i=1; i<=b; ++i) res *= 10;
    return res;
}

void process(int tes){
    int i,j,k, ans=0, save=N, last = 0;
    k = 1;

    printf("%d. ", tes);

    int tmp = fun(N);
    N += mi(tmp);

    while(N){
        int p = (N-last);
        if(p < 0) p += 10;
        p %= 10;
        ans = ans+p*k;
        N -= last;
        N /= 10;
        k *= 10;
        last = p;
    }
    if(fun(save)!=fun(ans)) cout<<"IMPOSSIBLE"<<endl;
    else cout<<ans<<endl;
}

int main(){
    int k = 0;
    while(cin>>N, N){
        process(++k);
    }
    return 0;
}

