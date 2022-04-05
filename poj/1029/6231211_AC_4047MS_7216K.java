

import java.util.Arrays;
import java.util.Scanner;

public class Main {
	
	public Scanner in = null;
	public int m, n, flag;
	public String[] str = new String[101];
	public int[][] a = new int[101][1020], b = new int[101][1020];
	public int[] ans = new int[1010], len = new int[101], tmp = new int[1010];
	public int[][] GA = new int[101][1020], GB = new int[101][1010];
	
	public boolean check(int now, int tye)
	{
		if(tye == 0)
		{
			for(int i=0; i<m; ++i)
			{
				if(str[i].charAt(0) == '<')
				{
					if(GA[i][now] == 0) return false;
				}
				else if(str[i].charAt(0) == '>')
				{
					if(GB[i][now] == 0) return false;
				}
				else
				{
					if(GA[i][now] == 1 || GB[i][now] == 1) return false;
				}
			}
			return true;
		}
		else
		{
			for(int i=0; i<m; ++i)
			{
				if(str[i].charAt(0) == '>')
				{
					if(GA[i][now] == 0) return false;
				}
				else if(str[i].charAt(0) == '<')
				{
					if(GB[i][now] == 0) return false;
				}
				else
				{
					if(GA[i][now] == 1 || GB[i][now] == 1) return false;
				}
			}
			return true;
		}
	}
	
	public void solve()
	{
		in = new Scanner(System.in);
		while(in.hasNext())
		{
			n = in.nextInt();
			m = in.nextInt();
			
			for(int i=0; i<m; ++i)
			{
				Arrays.fill(GA[i], 0);
				Arrays.fill(GB[i], 0);
			}
			
			flag = 1;
			
			for(int i=0; i<m; ++i)
			{
				int k = in.nextInt();
				len[i] = k;
				for(int j=0; j<k; ++j)
				{
					a[i][j] = in.nextInt() - 1;
					GA[i][a[i][j]] = 1;
				}
				for(int j=0; j<k; ++j)
				{
					b[i][j] = in.nextInt() - 1;
					GB[i][b[i][j]] = 1;
				}
				
				str[i] = in.next();
			}
			
			int cnt = 0, rec = -1;
			for(int i=0; i<n; ++i)
			{
				if(check(i, 0) || check(i, 1))
				{
					cnt++;
					rec = i;
				}
			}
			
			if(cnt > 1) System.out.println(0);
			else System.out.println(rec + 1);
		}
	}
	
	public static void main(String[] args)
	{
		Main a = new Main();
		a.solve();
	}
}

/*
5 3
2 1 2 3 4
<
1 1 4
=
1 2 5
=

5 2
2 1 2 3 4
=
1 5 3
<

 */
