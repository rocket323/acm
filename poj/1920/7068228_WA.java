import java.util.*;
import java.math.*;

public class Main
{

	int max(int a, int b){ return a > b ? a : b; }

	BigInteger dfs(int t_0, int t_1, int t_2, int k)
	{
		if(t_0 == 0 && t_1 == 0 && t_2 == 0) return BigInteger.ZERO;
		int sz = max(a[0][t_0], max(a[1][t_1], a[2][t_2]));
		//System.out.println(t_0 + " " + t_1 + " " + t_2 + " " + k + " " + sz);

		if(a[0][t_0] == sz)
		{
			if(k == 0) return dfs(t_0 - 1, t_1, t_2, 0);
			else if(k == 1) return dfs(t_0 - 1, t_1, t_2, 2).add(f(t_0 + t_1 + t_2 - 1)).add(one);
			else return dfs(t_0 - 1, t_1, t_2, 1).add(f(t_0 + t_1 + t_2 - 1)).add(one);
		}
		else if(a[1][t_1] == sz)
		{
			if(k == 1) return dfs(t_0, t_1 - 1, t_2, 1);
			else if(k == 0) return dfs(t_0, t_1 - 1, t_2, 2).add(f(t_0 + t_1 + t_2 - 1)).add(one);
			else return dfs(t_0, t_1 - 1, t_2, 0).add(f(t_0 + t_1 + t_2 - 1)).add(one);
		}
		else
		{
			if(k == 2) return dfs(t_0, t_1, t_2 - 1, 2);
			else if(k == 1) return dfs(t_0, t_1, t_2 - 1, 0).add(f(t_0 + t_1 + t_2 - 1)).add(one);
			else return dfs(t_0, t_1, t_2 - 1, 1).add(f(t_0 + t_1 + t_2 - 1)).add(one);
		}
	}

	BigInteger f(int n)
	{
		BigInteger ans = BigInteger.ONE, t = BigInteger.valueOf(2);
		while(n > 0)
		{
			if(n % 2 == 1) ans = ans.multiply(t);
			t = t.multiply(t);
			n >>= 1;
		}
		return ans.add(BigInteger.valueOf(-1));
	}

	void solve()
	{
		Scanner in = new Scanner(System.in);

		//for(int i=0; i<=10; ++i) System.out.println(f[i]);

		while(in.hasNext())
		{
			n = in.nextInt();
			for(int i=0; i<3; ++i) t[i] = in.nextInt();
			for(int i=0; i<3; ++i)
			{
				for(int j=t[i]; j>0; --j) a[i][j] = in.nextInt();
				a[i][0] = 0;
			}

			BigInteger ans = BigInteger.valueOf(-1);
			int k = -1;
			for(int i=0; i<3; ++i)
			{
				step[i] = dfs(t[0], t[1], t[2], i);
				if(k == -1 || step[i].compareTo(ans) < 0)
				{
					k = i + 1;
					ans = step[i];
				}
			}
			System.out.println(k + "\n" + ans);
		}
	}

	BigInteger one = BigInteger.ONE;
	int n;
	int[] t = new int[3];
	BigInteger[] step = new BigInteger[3];
	int[][] a = new int[3][100010];

	public static void main(String[] args)
	{
		Main a = new Main();
		a.solve();
	}
}
