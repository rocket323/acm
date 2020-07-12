#include <stdio.h>
#include <cstring>

const int N = 3010;
const int MAXV = 0x3F3F3F3F;
int n,m,v[N];
int mat[N][N];
int dis[N];
bool vis[N];
int res;
inline int min(int a, int b){
    return a < b ? a : b;
}
int Stoer_Wagner(int n) {
    int i, j;
    int res = MAXV;
    for (i = 0; i < n; i++)
        v[i] = i;
    while (n > 1) {
        int maxp = 1,prev = 0;
        for (i = 1;i < n;i++){ 
            dis[v[i]] = mat[v[0]][v[i]];
            if (dis[v[i]] > dis[v[maxp]])
                maxp = i;
        }
        memset(vis, 0, sizeof(vis));
        vis[v[0]] = true;
        for (i = 1;i < n;i++) {
            if (i == n - 1){ 
                res = min(res,dis[v[maxp]]);
                for (j = 0; j < n; j++){ 
                    mat[v[prev]][v[j]] += mat[v[j]][v[maxp]];
                    mat[v[j]][v[prev]] = mat[v[prev]][v[j]];
                }
                v[maxp] = v[--n];
            }
            vis[v[maxp]] = true;
            prev = maxp;
            maxp = -1;
            for (j = 1;j < n;j++)
                if (!vis[v[j]]){
                    dis[v[j]] += mat[v[prev]][v[j]];
                    if (maxp == -1 || dis[v[maxp]] < dis[v[j]])
                        maxp = j;
                }
        }
    }
    return res;
}
int main(){
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(mat, 0, sizeof (mat));
        int x,y,z;
        while (m--) {
            scanf("%d%d%d", &x, &y, &z);
            mat[x-1][y-1] += z;
            mat[y-1][x-1] += z;
        }
        printf("%d\n",Stoer_Wagner(n));
    }
    return 0;
}
