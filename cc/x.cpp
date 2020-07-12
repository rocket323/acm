#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int phi[maxl];
void getPhi(int n)
{
    int minDiv;
    for(int i=1;i<n;i++)
        phi[i]=i;

    for(int i=2;i*i<n;i++)  //最小质因数
        if(phi[i]==i)
        {
            for(int j=i*i;j<n;j+=i)
                phi[j]=i;
        }

    phi[1]=1;
    ll ans = 0;
    for(int i=2;i<n;i++)
    {
        minDiv=phi[i];
        if((i/phi[i])%phi[i]==0)
            phi[i]=phi[i/phi[i]]*phi[i];
        else
            phi[i]=phi[i/phi[i]]*(phi[i]-1);

        // printf("%d %d\n", i, phi[i]);
        if (phi[i] != i - 1)
            ans += phi[i];
    }
    cout << ans << endl;
}

int main() {
    getPhi(1e5 + 1);
    // getPhi(10);

    return 0;
}

