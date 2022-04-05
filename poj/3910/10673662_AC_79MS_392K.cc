#include <stdio.h> 
#include <algorithm> 
#define ll long long 
#define mod 1000000007 
using namespace std; 

int n, x[1001]; 
int a[1001]; 

void init() 
{ 
    for(int i=0; i<n; ++i) scanf("%d", &x[i]); 
     sort(x, x+n); 
} 

void solve() 
{ 
     a[0] = x[0]; 
    long long ans = a[0]; 
    for(int i=1; i<n; ++i) 
     { 
         a[i] = x[i]; 
        for(int j=0; j<i; ++j) 
         { 
            if(!(x[i]%x[j])) a[i] -= a[j]; 
         } 
         ans = ((ll)ans * a[i]) % mod; 
     } 
     printf("%lld\n", ans); 
} 

int main() 
{ 
    while(scanf("%d", &n)!=EOF) 
     { 
         init(); 
         solve(); 
     } 
    return 0; 
} 