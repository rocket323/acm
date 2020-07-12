#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define sd(x) scanf("%d", &(x))
#define pii pair<int, int>
#define F first
#define S second
#define vi vector<int>
#define vll vector<ll>

#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif


const int g = 3, mod = 998244353, p = 998244353;

inline int add(int x, int y){ x += y; if(x >= mod) x -= mod; return x;}
inline int sub(int x, int y){ x -= y; if(x < 0) x += mod; return x;}
inline int mul(int x, int y){ return (x * 1ll * y) % mod;}
inline int powr(int a, ll b){
    int x = 1 % mod;
    while(b){
        if(b & 1) x = mul(x, a);
        a = mul(a, a);
        b >>= 1;
    }
    return x;
}
inline int inv(int a){ return powr(a, mod - 2);}

const int MX = 18;
int W[1 << MX], invW[1 << MX]; // max polynomial input/output -> (1 << MX)
int maxn;

void precompute_powers(){
    int p2 = p - 1, MAXN = 0;
    while(p2 % 2 == 0){
        p2 >>= 1;
        MAXN ++;
    }
    MAXN = min(MAXN, MX);
    int g1 = powr(g, (p - 1) >> MAXN);
    maxn = 1 << MAXN;
    int st = 1;
    for(int i = 0; i < maxn; i++){
        W[i] = st;
        st = mul(st, g1);
    }
    for(int i = 0; i < maxn; i++){
        invW[i] = (i == 0) ? 1 : W[maxn - i];
    }
}

void fft (vector<int> & a, bool invert) {
    int n = (int) a.size();

    for (int i=1, j=0; i<n; ++i) {
        int bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }

    for (int len=2; len<=n; len<<=1) {
        for (int i=0; i<n; i+=len) {
            int ind = 0,ADD = maxn/len;
            for (int j=0; j<len/2; ++j) {
                int u = a[i+j],  v = mul(a[i+j+len/2], (invert?invW[ind]:W[ind]));
                a[i+j] = add(u, v);
                a[i+j+len/2] = sub(u, v);
                ind += ADD;
            }
        }
    }
    if (invert){
        int invn = inv(n);
        for (int i=0; i<n; ++i) a[i] = mul(a[i], invn);
    }
}

vi add(vi a, vi b){
    vi ret(max(a.size(), b.size()));
    for(int i = 0; i < ret.size(); i++){
        ret[i] = add(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
    }
    return ret;
}

vi sub(vi a, vi b){ 
    vi ret(max(a.size(), b.size()));
    for(int i = 0; i < ret.size(); i++){
        ret[i] = sub(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
    }
    return ret;
}

vi mul(vi a, vi b){
    int sz = a.size() + b.size() - 1;
    int k = 0;
    while((1 << k) < sz) k++;
    a.resize(1 << k); b.resize(1 << k);
    fft(a, 0); fft(b, 0);
    for(int i = 0; i < (1 << k); i++)
        a[i] = mul(a[i], b[i]);
    fft(a, 1);
    a.resize(sz);
    return a;
}

vi inverse(vi a, int sz){
    assert(a[0] != 0);
    vi x = {inv(a[0])};
    while(x.size() < sz){
        vi temp(a.begin(), a.begin() + min(a.size(), 2 * x.size()));
        vi nx = mul(mul(x, x), temp);
        x.resize(2 * x.size());
        for(int i = 0; i < x.size(); i++)
            x[i] = sub(add(x[i], x[i]), nx[i]);
    }
    x.resize(sz);
    return x;
}

vi truncate_end(vi v){
    while(!v.empty() && v.back() == 0) v.pop_back();
    if(v.empty()) v = {0};
    return v;
}

void print(vi v){
    cerr << "["; 
    for(int i = 0; i < v.size(); i++){
        cerr << v[i];
        if(i + 1 != v.size()) cerr <<" ";
        else cerr << "]";
    }
    cerr << endl;
}

vi _inv;
pair<vi, vi> divmod(vi f, vi g){
    if(f.size() < g.size()) return {{0}, f};
    int sz = f.size() - g.size() + 1;
    reverse(f.begin(), f.end()); reverse(g.begin(), g.end());
    vi inv2 = _inv;
    inv2.resize(sz);
    vi _p = f; _p.resize(sz);
    vi q = mul(inv2, _p);
    q.resize(sz);
    reverse(q.begin(), q.end()); reverse(f.begin(), f.end()); reverse(g.begin(), g.end());
    return {q, truncate_end(sub(f, mul(g, q)))};
}

vi powr_mod(long long n, vi & f){
    if(n == 0) return {1};
    if(n & 1){
        return divmod(mul({0, 1}, powr_mod(n - 1, f)), f).second;
    }
    vi p = powr_mod(n >> 1, f);
    return divmod(mul(p, p), f).second;
}

const int N = 1005;
int a[N], c[N], depth[N], reach[N];
int leaf_or_root[N];
vi con[N], leaves;
vector<int> temp;
vi subtree_leaves[N];
void dfs(int s = 1, int p = -1, int prob = 1, int d = 0){
    temp.push_back(s);
    depth[s] = d;
    int cnt = 0;
    reach[s] = prob;

    for(int v : con[s]) if(v != p){
        cnt++;
    }

    int np = mul(prob, inv(cnt));
    for(int v : con[s]) if(v != p){
        dfs(v, s, np, d + 1);
    }

    if(!cnt){
        c[2 * d] = add(c[2 * d], prob);
        leaves.push_back(s);
        leaf_or_root[s] = 1;
        for(int anc : temp) subtree_leaves[anc].push_back(s);
    }
    temp.pop_back();
}

int dp[N][N];
int E[N], t[N];

int main(){
    precompute_powers();
    leaf_or_root[1] = 1;
    int n, m; sd(n);
    // handle n = 1
    for(int i = 1; i < n; i++){
        int u, v;
        sd(u); sd(v);
        con[u].push_back(v);
        con[v].push_back(u);
    }

    dfs();
    int k = 2 * n - 2;
    vi v = {1};
    for(int i = 1; i <= k; i++) v.push_back(sub(0, c[i]));;
    _inv = inverse(v, k + 1);
    reverse(v.begin(), v.end());


    for(int i = 1; i <= 2 * n - 2; i++){
        for(int j = 1; j <= n; j++){
            for(int l : leaves){
                if(2 * depth[l] <= i) dp[i][j] = add(dp[i][j], mul(reach[l], dp[i- 2 * depth[l]][j]));
            }
            if(depth[j] <= i){
                if(j != 1) dp[i][j] = add(dp[i][j], reach[j]);
                if(!leaf_or_root[j] || j == 1)
                for(int l : subtree_leaves[j]){
                    if(2 * depth[l] - depth[j] <= i) dp[i][j] = add(dp[i][j], reach[l]);
                }
            }
            // trace(i, j, dp[i][j]);
        }
    }
    sd(m);
    int sm = 0;
    for(int j = 1; j <= 2 * n - 2; j++) sm = add(sm, mul(j, c[j]));

    sm = inv(sm);
    int q;
    for(int i = 1; i <= m; i++){
        sd(t[i]);
    }

    sd(q);

    for(int i = 1; i <= m; i++){
        if(t[i] > q) continue;
        if(n == 1){
            E[1] = add(E[1], q - t[i] + 1);
            continue;
        }
        
        E[1] = add(E[1], 1);
        if(t[i] == q) continue;
        int rem = q - t[i];

        if(rem <= 2 * n - 2){
            for(int j = 1; j <= n; j++)
                E[j] = add(E[j], dp[rem][j]);
            continue;
        }

        vi s = powr_mod(rem - 1, v);
        int s_s = 0;

        /*for(auto it : s) cerr<<it<<" ", s_s = add(s_s, it); cerr << endl;
        trace(s_s, inv(sm));*/

        for(int j = 1; j <= n; j++){
            int delta = mul(reach[j], mul(2 - leaf_or_root[j], sm));
            int x = 0;
            for(int ind = 1; ind <= 2 * n - 2 && ind - 1 < s.size(); ind++){
                x = add(x, mul(s[ind - 1], sub(dp[ind][j], mul(delta, ind))));
                // if(s[ind-1]) trace(j, ind, dp[ind][j]);
            }
            E[j] = add(E[j], add(x, mul(delta, rem)));
         }
    }

    for(int i = 1; i <= n; i++) printf("%d ", E[i]); printf("\n");
}

