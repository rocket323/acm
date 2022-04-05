import java.math.BigInteger;
import java.util.Scanner;

public class Main
{

	public static BigInteger calc(String str)
	{
		BigInteger ans = null;
		if(str.charAt(0) == '+') ans = new BigInteger(str.substring(1));
		else ans = new BigInteger(str);
		
		return ans;
	}

	public static void main(String[] args)
	{
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();

		while(t-- > 0)
		{
			String a = in.next();
			String b = in.next();

			System.out.println(calc(a).add(calc(b)));
		}
	}
}

