
import java.math.BigInteger;
import java.util.Scanner;

public class Main
{
	
	public BigInteger pow(int x)
	{
		BigInteger X = new BigInteger(x+"");
		BigInteger res = BigInteger.ONE;
		for(int i=1; i<=N; ++i)
			res = res.multiply(X);
		return res;
	}
	
	public int check(int x)
	{
		int cnt = 0;
		for(int i=2; i*i<=x; ++i)
		{
			if(x%i!=0) continue;
			cnt = (cnt+1)%2;
			if(x%(i*i)==0) return -1;
			while(x%i==0) x /= i;
		}
		if(x>1) cnt = (cnt+1)%2;
		return cnt;
	}
	
	public void go(int x)
	{
		int k = check(x);
		if(k==0) res = res.add(pow(M/x));
		else if(k==1) res = res.subtract(pow(M/x));
	}
	
	public void solve()
	{
		N = in.nextInt();
		M = in.nextInt();
		for(int i=1; i<=N; ++i) res = res.multiply(new BigInteger(M+""));
		
		for(int i=2; i*i<=M; ++i)
		{
			if(M%i!=0) continue;
			go(i);
			if(i*i!=M) go(M/i);
		}
		go(M);
		System.out.println(res);
	}
	
	private Scanner in = new Scanner(System.in);
	private int N, M;
	private BigInteger res = BigInteger.ONE;
	private BigInteger NEG = new BigInteger("-1");
	
	public static void main(String[] args)
	{
		Main a = new Main();
		a.solve();
	}

}
