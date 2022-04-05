import java.util.Arrays;
import java.util.Scanner;

public class Main {
	
	public Scanner in = null;
	public long[][][] f = new long[21][21][2];
	public int[] ans = new int[21];
	public boolean[] vis = new boolean[21];
	
	public void go(int n, long c)
	{
		
		f[1][1][1] = f[1][1][0] = 1;
		
		for(int i=2; i<=n; ++i)
		{
			f[i][1][0] = f[i][i][1] = 0;
			
			for(int j=1; j<i; ++j)
			{
				f[i][j+1][0] = f[i][j][0] + f[i-1][j][1];
				f[i][i-j][1] = f[i][j+1][0];
			}
		}
	}
	
	public int find(int x)
	{
		int k = 1;
		for(int i=1; i<=x; ++i)
		{
			while(vis[k]) k++;
			k++;
		}
		return k - 1;
	}
	
	public void out(int n, long c)
	{
		Arrays.fill(vis, false);
		
		int i = 1;
		while(f[n][i][0] + f[n][i][1] < c)
		{
			c -= f[n][i][0] + f[n][i][1];
			i++;
		}
		ans[1] = i;
		vis[ans[1]] = true;
		
		if(n >= 2)
		{
			for(i=1; i<=n-1; ++i)
			{
				long tmp;
				if(i < ans[1]) tmp = f[n-1][i][1];
				else tmp = f[n-1][i][0];
				
				if(tmp < c) c -= tmp;
				else
				{
					if(i < ans[1]) ans[2] = i;
					else ans[2] = i + 1;
					
					vis[ans[2]] = true;
					break;
				}
			}
		}
		
		for(i=3; i<=n; ++i)
		{
			int id = ans[i - 1];
			for(int j=1; j<ans[i-1]; ++j) if(vis[j]) id--;
			
			if(ans[i-2] < ans[i-1])
			{
				for(int k=1; k<id; ++k)
				{
					if(f[n-i+1][k][1] < c) c -= f[n-i+1][k][1];
					else
					{
						ans[i] = find(k);
						break;
					}
				}
			}
			else
			{
				for(int k=id; k<=n-i+1; ++k)
				{
					if(f[n-i+1][k][0] < c) c -= f[n-i+1][k][0];
					else
					{
						ans[i] = find(k);
						break;
					}
				}
			}
			vis[ans[i]] = true;
		}
		
		for(i=1; i<n; ++i) System.out.print(ans[i] + " ");
		System.out.println(ans[n]);
	}
	
	public void solve()
	{
		in = new Scanner(System.in);
		int t = in.nextInt();
		
		while(t-- > 0)
		{
			int n = in.nextInt();
			long c = in.nextLong();
			go(n, c);
			out(n, c);
		}
	}
	
	public static void main(String[] args)
	{
		Main a = new Main();
		a.solve();
	}
}
