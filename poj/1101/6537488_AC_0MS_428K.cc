#include <stdio.h>

typedef struct{
 int x, y;
}queue;
queue q[10000];

char g[100][100];
int v[100][100];
int m, n;
int x[4] = {1, -1, 0, 0};
int y[4] = {0, 0, 1, -1};

int good(int x, int y){
 if(x >= 0 && x < m + 2 && y >= 0 && y < n + 2)
  return 1;
 else
  return 0;
}

int main(){
 int i, j, c1 = 1, c2;
 int top, tail;
 int sx, sy, ex, ey, tx, ty;

 while(scanf("%d %d", &n, &m) && m != 0 && n != 0){
  getchar();
  c2 = 1;
  for(i = 1; i <= m; i++)
   gets(&g[i][1]);
  for(i = 0; i < n + 2; i++)
   g[0][i] = g[m + 1][i] = ' ';
  for(i = 1; i <= m; i++)
   g[i][0] = g[i][n + 1] = ' ';

  printf("Board #%d:\n", c1++);
  while(scanf("%d %d %d %d", &sy, &sx, &ey, &ex)){
   if(sx == 0 && sy == 0 && ex == 0 && ey == 0)
    break;
   for(i = 0; i < m + 2; i++){
    for(j = 0; j < n + 2; j++)
     v[i][j] = -1;
   }
   g[sx][sy] = g[ex][ey] = ' ';

   v[sx][sy] = 0;
   top = tail = 0;
   q[top].x = sx;
   q[top].y = sy;

   while(top <= tail && v[ex][ey] == -1){
    for(i = 0; i < 4; i++){
     tx = q[top].x + x[i];
     ty = q[top].y + y[i];
     while(good(tx, ty) && g[tx][ty] == ' ' && v[tx][ty] == -1){
      tail++;
      q[tail].x = tx;
      q[tail].y = ty;
      v[tx][ty] = v[q[top].x][q[top].y] + 1;
      tx += x[i];
      ty += y[i];
     }
    }
    top++;
   }
   g[sx][sy] = g[ex][ey] = 'X';

   if(v[ex][ey] == -1)
    printf("Pair %d: impossible.\n", c2++);
   else
    printf("Pair %d: %d segments.\n", c2++, v[ex][ey]);
  }
  printf("\n");
 }
 return 0;
}