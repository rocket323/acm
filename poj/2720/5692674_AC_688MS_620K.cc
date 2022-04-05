/*

	欧拉函数

*/

#include <cstdio>

#include <cstring>



int			M	= 10000000;

int			B , x , n;



int			reco	[120][120];



inline	long long	mod( long long a , long long b ){ return a <= b ? a : b + a % b; }



int	powerMod( int a , int p , int m )

{

	long long	ret , w;



	w = a; ret = 1;

	while( p )

	{

		if( p & 1 ) ret = mod( ret * w , m );

		p >>= 1;

		w = mod( w * w , m );

	}



	return	ret;

}



int	eulerPhi( int n )

{

	int		ret = n;

	int		m = 2;



	while( m * m <= n )

	{

		if( n % m == 0 )

		{

			ret = ret / m * (m - 1);

			while( n % m == 0 )

				n /= m;

		}

		m ++;

	}



	if( n > 1 ) ret = ret / n * (n - 1);



	return	ret;

}



int	calc(int p , int m)

{

	if( p == 0 ) return 1;



	int		phi = eulerPhi( m );

	int		v = calc( p - 1 , phi );



	return	powerMod( B , v , m );

}



void	solve()

{

	int		ret;

	char		line	[10];



	if( reco[B][x] < 0 )

		reco[B][x] = calc(x , M) % M;



	ret = reco[B][x];



	sprintf(line , "%.7d" , ret);

	printf("%s\n" , line + (7 - n));

}



int	main()

{

	//freopen("in.txt" , "r" , stdin);



	memset( reco , 0xff , sizeof(reco));



	while( scanf("%d" , &B) , B )

	{

		scanf("%d%d" , &x , &n);



		solve();

	}



	return 0;

}
