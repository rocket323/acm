import java.util.*;
import java.math.*;

public class Main
{

	int max(int a, int b){ return a > b ? a : b; }

	int dfs(int t_0, int t_1, int t_2, int k)
	{
		if(t_0 == 0 && t_1 == 0 && t_2 == 0) return 0;
		int sz = max(a[0][t_0], max(a[1][t_1], a[2][t_2]));

		if(a[0][t_0] == sz)
		{
			if(k == 0) return dfs(t_0 - 1, t_1, t_2, 0);
			else if(k == 1) return (dfs(t_0 - 1, t_1, t_2, 2) + f(t_0 + t_1 + t_2 - 1) + 1) % mod;
			else return (dfs(t_0 - 1, t_1, t_2, 1) + f(t_0 + t_1 + t_2 - 1) + 1) % mod;
		}
		else if(a[1][t_1] == sz)
		{
			if(k == 1) return dfs(t_0, t_1 - 1, t_2, 1);
			else if(k == 0) return (dfs(t_0, t_1 - 1, t_2, 2) + f(t_0 + t_1 + t_2 - 1) + 1) % mod;
			else return (dfs(t_0, t_1 - 1, t_2, 0) + f(t_0 + t_1 + t_2 - 1) + 1) % mod;
		}
		else
		{
			if(k == 2) return dfs(t_0, t_1, t_2 - 1, 2);
			else if(k == 1) return (dfs(t_0, t_1, t_2 - 1, 0) + f(t_0 + t_1 + t_2 - 1) + 1) % mod;
			else return (dfs(t_0, t_1, t_2 - 1, 1) + f(t_0 + t_1 + t_2 - 1) + 1) % mod;
		}
	}

	int f(int n)
	{
		int ans = 1, t = 2;
		while(n > 0)
		{
			if(n % 2 == 1) ans = (int)((long)ans * t % mod); 
			t = (int)((long)t * t % mod);
			n >>= 1;
		}
		return (ans - 1 + mod) % mod;
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

			for(int i=0; i<3; ++i)
			{
				if(a[i][t[i]] != n) continue;
				int step = dfs(t[0], t[1], t[2], i);
				System.out.print(i + 1 + "\n" + step);
			}
		}
	}

	int mod = 1000000;
	int n;
	int[] t = new int[3];
	int[][] a = new int[3][100010];

	public static void main(String[] args)
	{
		Main a = new Main();
		a.solve();
	}
}
