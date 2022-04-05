#include <iostream>

#include <algorithm>

#define MaxN 1000010

#define INF 10000000

using namespace std;



struct node

{

    int s, t;

}E[1001];



int A, B, N, L;

bool flag = 1, can[MaxN];

int f[MaxN], Q[MaxN];

int head, tail;



bool cmp(node A, node B){ return A.s<B.s; }



void init()

{

    scanf("%d%d", &N, &L);

    scanf("%d%d", &A, &B);

    for(int i=1; i<=N; ++i)

    {

        scanf("%d%d", &E[i].s, &E[i].t);

        if(E[i].t-E[i].s>2*B) 

        {

            flag = 0;

        }

    }

    sort(E+1, E+1+N, cmp);

}



int Min(int a, int b){ return (a<b)?a:b; }



void solve()

{

    if(!flag)

    {

        printf("-1\n");

        return;

    }

    for(int i=0; i<=L; ++i) can[i] = 1;

    for(int i=1; i<=N; ++i)

        for(int j=E[i].s+1; j<E[i].t; ++j)

            can[j] = 0;



    f[0] = 0;

	head=1; tail=1;

    for(int i=1; i<=L; ++i)

    {

        f[i] = INF;



		int j=i-2*A;

		if(j<0) continue;

		while(tail>1&&head<tail)

		{

			if(f[j]<=f[Q[tail-1]]) tail--;

			else break;

		}

		if(can[j])

		{

			Q[tail] = j;

			tail++;

		}

	

		if(!can[i]||(i&1)) continue;



		while((head<tail))

		{

			if(Q[head]>=i-2*B)

				break;

			else head++;

		}

		if(head<tail)

			f[i] = f[Q[head]]+1;



	}

    if(f[L]>=INF)

	{

        printf("-1\n");

	}

    else

        printf("%d\n", f[L]);

}



int main()

{

    freopen("divide.9.in", "r", stdin);

    init();

    solve();

    return 0;

}


