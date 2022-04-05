import java.math.BigInteger;
import java.util.Scanner;

public class Main
{

	public BigInteger[][] f = new BigInteger[100][100];
	public BigInteger[] val = new BigInteger[105];

	public void solve()
	{
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();
		for(int i=0; i<=100; ++i) val[i] = new BigInteger(i + "");
		while(t-- > 0)
		{
			int n = in.nextInt();
			int k = in.nextInt();

			for(int i=0; i<=n; ++i) for(int j=0; j<=k; ++j) f[i][j] = BigInteger.ZERO;
			f[0][0] = BigInteger.ONE;
			f[1][1] = BigInteger.ONE;

			for(int i=2; i<=n; ++i)
			{
				f[i][0] = BigInteger.ZERO;
				for(int j=1; j<=k && j<=2*i; ++j)
				{
					f[i][j] = val[j].multiply(f[i-1][j]).add(val[2*i-j].multiply(f[i-1][j-1]));
				}
			}
			System.out.println(f[n][k]);
		}
	}

	public static void main(String[] args)
	{
		Main a = new Main();
		a.solve();
	}
}

