import java.math.BigInteger;
import java.util.Scanner;

public class Main
{

	public void getC()
	{
		for(int i=0; i<51; ++i) c[i][0] = c[i][i] = BigInteger.ONE;

		for(int i=1; i<51; ++i)
		{
			for(int j=1; j<i; ++j)
			{
				c[i][j] = c[i-1][j].add(c[i-1][j-1]);
			}
		}
	}

	public BigInteger pow(int n)
	{
		if(n==0) return BigInteger.ONE;
		BigInteger tmp = pow(n/2);

		if(n % 2 == 1) return tmp.multiply(tmp).multiply(two);
		else return tmp.multiply(tmp);
	}

	void go()
	{
		f[1] = BigInteger.ONE;

		for(int i=2; i<51; ++i)
		{
			f[i] = pow(i*(i-1)/2);

			for(int j=1; j<i; ++j)
			{
				f[i] = f[i].add( f[j].multiply(c[i-1][j-1]).multiply(pow((i-j)*(i-j-1)/2)).multiply(neg) );
			}
		}
	} 

	public void solve()
	{
		in = new Scanner(System.in);

		two = new BigInteger("2");
		neg = new BigInteger("-1");

		getC();
		go();

		n = in.nextInt();
		while(n != 0)
		{
			System.out.println(f[n]);
			n = in.nextInt();
		}
	}

	private BigInteger neg = null;
	private BigInteger two = null;
	private BigInteger[] f = new BigInteger[51];
	private BigInteger[][] c = new BigInteger[51][51];
	private int n;
	private Scanner in = null;

	public static void main(String[] args)
	{
		Main a = new Main();
		a.solve();
	}
}
