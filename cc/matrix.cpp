//teja349
#include <bits/stdc++.h>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <utility>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <iomanip> 
//setbase - cout << setbase (16); cout << 100 << endl; Prints 64
//setfill -   cout << setfill ('x') << setw (5); cout << 77 << endl; prints xxx77
//setprecision - cout << setprecision (14) << f << endl; Prints x.xxxx
//cout.precision(x)  cout<<fixed<<val;  // prints x digits after decimal in val

using namespace std;
#define f(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) f(i,0,n)
#define fd(i,a,b) for(i=a;i>=b;i--)
#define pb push_back
#define mp make_pair
#define vi vector< int >
#define vl vector< ll >
#define ss second
#define ff first
#define ll long long
#define pii pair< int,int >
#define pll pair< ll,ll >
#define sz(a) a.size()
#define inf (1000*1000*1000+5)
#define all(a) a.begin(),a.end()
#define tri pair<int,pii>
#define vii vector<pii>
#define vll vector<pll>
#define viii vector<tri>
#define mod (998244353)
#define pqueue priority_queue< int >
#define pdqueue priority_queue< int,vi ,greater< int > >

ll matr[25][2000][2000];
ll ans[2000],ans1[2000];
ll par[412],childs[412],inv[412];
ll iinf;
vector<vi> adj(412);
// dfs.
ll dfs(ll cur,ll previ){
    par[cur]=previ;
    ll i;
    ll cnt=0;
    rep(i,adj[cur].size()){
        if(adj[cur][i]!=previ){
            dfs(adj[cur][i],cur);
            cnt++;
        }
    }

    childs[cur]=cnt;

    return 0;
}
ll t[412],dp[412];
int up[412],down[412];
int main(){
    std::ios::sync_with_stdio(false);
    iinf =mod;
    iinf*=mod;
    ll n;
    cin>>n;
    ll i;
    ll u,v;
    ll j,k;
    // taking input
    rep(i,n-1){
        cin>>u>>v;
        assert(u>=1 && u<=n);
        assert(v>=1 && v<=n);
        u--;
        v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    inv[0]=1;
    inv[1]=1;
    // finding inverse of numbers
    f(i,2,n+10){
        inv[i]=inv[mod%i]*(mod/i);
        inv[i]%=mod;
        inv[i]*=-1;
        inv[i]%=mod;
        inv[i]+=mod;
    }
    ll m;
    cin>>m;
    rep(i,m){
        cin>>t[i];
    }
    ll q;
    cin>>q;
    ll sumi=0;
    // special case.
    if(n==1){
        rep(i,m){
            if(t[i]<=q)
                sumi+=q-t[i]+1;
        }
        cout<<sumi<<endl;
        return 0;
    }

    dfs(0,-1);
    ll counter=n;
    ll papa;
    // determining which all vertices need two directions and which need only one direction(i.e root and leaves)
    // constant optimisation
    rep(i,n){
        if(i==0 || childs[i]==0){
            down[i]=counter++;
            up[i]=down[i];
        }
        else{
            down[i]=counter++;
            up[i]=counter++;
        }
    }
    // construction of matrix
    rep(i,n){

        if(i!=0){
            papa=par[i];
            matr[0][down[i]][down[papa]]=inv[childs[papa]];
            if(!childs[i]){
                matr[0][up[i]][down[papa]]=inv[childs[papa]];
            }
            else{
                rep(j,adj[i].size()){
                    if(adj[i][j]!=par[i]){
                        papa=adj[i][j];
                        matr[0][up[i]][up[papa]]=1;
                    }
                }
            }
        }
        else{
            rep(j,adj[i].size()){
                if(adj[i][j]!=par[i]){
                    papa=adj[i][j];
                    matr[0][up[i]][up[papa]]=1;
                    matr[0][down[i]][up[papa]]=1;
                    //matr[0][2*i+counter][2*papa+counter+1]=1;
                }
            }
        }

    }

    //construction for the sum part in matrix
    rep(i,n){
        matr[0][i][i]=1;

        if(i==0 || childs[i]==0){
            matr[0][i][up[i]]=1;
        }
        else{
            matr[0][i][up[i]]=1;
            matr[0][i][down[i]]=1;
        }
    }

    // precomputing 2 powers of the matrix
    ll mask=1;
    while((1<<mask)<=q){
        rep(i,counter){
            rep(k,counter){
                // optimisation
                if(matr[mask-1][i][k]==0)
                    continue;
                rep(j,counter){
                    matr[mask][i][j]+=matr[mask-1][i][k]*matr[mask-1][k][j];
                    if(matr[mask][i][j]>iinf)
                        matr[mask][i][j]-=iinf;
                }
            }
        }
        rep(i,counter){
            rep(j,counter){
                matr[mask][i][j]%=mod;
            }
        }
        mask++;
    }
    ll num;
    rep(i,m){
        num=q-t[i]+1;
        rep(j,counter){
            ans[j]=0;
        }
        ans[up[0]]=1;
        ans[down[0]]=1;
        if(num<=0)
            continue;
        mask=0;
        // finding matrix power * base case in K*K *logn ( assuming K is matrix size and n is power to which it is being raised to )
        while(num){
            if(num%2){

                rep(k,counter){
                    // optimisation.
                    if(ans[k]==0)
                        continue;
                    rep(j,counter){
                        ans1[j]+=matr[mask][j][k]*ans[k];
                        if(ans1[j]>iinf)
                            ans1[j]-=iinf;
                    }
                }
                rep(j,counter){
                    ans[j]=ans1[j]%mod;
                    ans1[j]=0;
                }
            }
            num/=2;
            mask++;
        }

        rep(j,n){
            dp[j]+=ans[j];
        }

    }
    rep(i,n){
        dp[i]%=mod;
        cout<<dp[i]<<" ";
    }
    cout<<endl;

    return 0;   
}

