import java.util.*;
import java.math.*;

public class Main
{

	static BigInteger C(int n, int m)
	{
		BigInteger ans = BigInteger.ONE;
		for(int i=0; i<m; ++i) ans = ans.multiply(BigInteger.valueOf(n - i));
		for(int i=1; i<=m; ++i) ans = ans.divide(BigInteger.valueOf(i));
		return ans;
	}

	public static void main(String[] args)
	{
		int n = 6;
		Scanner in = new Scanner(System.in);

		while(in.hasNext())
		{
			n = in.nextInt();
			if(n == -1) break;
			BigInteger ans = C(2 * n, n).divide(BigInteger.valueOf(n + 1));
			System.out.println(ans);
		}
	}
}

