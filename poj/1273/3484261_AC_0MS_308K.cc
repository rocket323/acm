#include <cstdio>
#include <cstring>

const int SIZEN = 200 + 5;
const int SIZEM = 200 + 5;
const int SIZEE = 2 * SIZEM + 5;
const int MAXIMUMC = 2000000000;

struct Node {
	int v, c, index, nex;
} E[SIZEE];

int R[SIZEN], P[SIZEN], W[SIZEN], LV[SIZEN], Q[SIZEN], nex[SIZEN], N, M, EN, PL;

void edgeAddProcess( int a, int b, int c )
{
	EN++;
	E[EN].v = b;
	E[EN].c = c;
	E[EN].nex = R[a];
	R[a] = EN;
}

void edgeAdd( int a, int b, int c )
{
	edgeAddProcess( a, b, c );
	edgeAddProcess( b, a, 0 );
	E[EN-1].index = EN - 2;
	E[EN-2].index = EN - 1;
}

void buildGraph()
{
	int i, a, b, c;

	memset( R, 0, sizeof(R) );
	EN = 0;
	for ( i = 0; i < M; i++ ) {
		scanf( "%d %d %d", &a, &b, &c );
		edgeAdd( a, b, c );
	}
}

int min( int a, int b )
{
	return ( a>b ) ? ( b ) : ( a );
}

void calcLV( int S, int T )
{
	int st, sf, next, i;

	memset( LV, -1, sizeof(LV) );
	Q[st=sf=1] = S;
	LV[S] = 0;
	while ( st <= sf ) {
		next = R[Q[st]];
		while ( next != 0 ) {
			if ( LV[E[next].v]==-1 && E[next].c>0 ) {
				LV[E[next].v] = LV[Q[st]] + 1;
				sf++;
				Q[sf] = E[next].v;
			}
			next = E[next].nex;
		}
		st++;
	}
}

int maxFlow( int S, int T )
{
	int i, u, d, bneck, flow = 0;

	while ( calcLV(S, T), LV[T]!=-1 ) {
		u = S;
		PL = 1;
		P[PL] = S;
		W[PL] = 0;
		memcpy( nex, R, sizeof(nex) );
		while ( nex[S] != 0 ) {
			if ( u!=T && nex[u]!=0 && E[nex[u]].c>0 && LV[E[nex[u]].v]==LV[u]+1 ) {
				PL++;
				P[PL] = E[nex[u]].v;
				W[PL] = nex[u];
				u = E[nex[u]].v;
			} else if ( u == T ) {
				d = MAXIMUMC;
				for ( i = PL; i > 1; i-- ) d = min( d, E[W[i]].c );
				for ( i = PL; i > 1; i-- ) {
					E[W[i]].c -= d;
					E[E[W[i]].index].c += d;
					if ( E[W[i]].c == 0 ) PL = i-1;
				}
				flow += d;
				u = P[PL];
			} else {
				while ( u!=S && nex[u]==0 )
					u = P[--PL];
				nex[u] = E[nex[u]].nex;
			}
		}
	}
	return flow;
}

int main( void )
{
	while ( scanf("%d %d", &M, &N) != EOF ) {
		buildGraph();
		printf( "%d\n", maxFlow(1, N) );
	}
	return 0;
}