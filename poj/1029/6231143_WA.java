

import java.util.Arrays;
import java.util.Scanner;

public class Main {
	
	public Scanner in = null;
	public int m, n, flag;
	public String[] str = new String[101];
	public int[][] a = new int[101][1020], b = new int[101][1020];
	public int[] ans = new int[1010], len = new int[101], tmp = new int[1010];
	
	public void out(int ans[])
	{
		System.out.println("\n******************");
		for(int i=0; i<n; ++i) System.out.print(ans[i] + " ");
		System.out.println("\n******************");
	}
	
	public int go1()
	{
		Arrays.fill(ans, 0, n, 1);
		for(int i=0; i<m; ++i)
		{
			Arrays.fill(tmp, 0, n, 0);
			if(str[i].charAt(0) == '<')
			{
				for(int j=0; j<len[i]; ++j) ans[b[i][j]] = 0;
				for(int j=0; j<len[i]; ++j) tmp[a[i][j]] = 1;
				for(int j=0; j<n; ++j) ans[j] = ans[j] & tmp[j];
			}
			else if(str[i].charAt(0) == '>')
			{
				for(int j=0; j<len[i]; ++j) tmp[b[i][j]] = 1;
				for(int j=0; j<len[i]; ++j) ans[a[i][j]] = 0;
				for(int j=0; j<n; ++j) ans[j] = ans[j] & tmp[j];
			}
			else
			{
				for(int j=0; j<len[i]; ++j) ans[a[i][j]] = 0;
				for(int j=0; j<len[i]; ++j) ans[b[i][j]] = 0;
			}
		}	
	
		int cnt = 0, ret = -1;
		for(int i=0; i<n; ++i)
		{
			if(ans[i] == 1){ cnt++; ret = i; }
		}
		if(cnt > 1)
		{
			flag = 0;
			return -1;
		}
		else return ret;
	}
	
	public int go2()
	{
		Arrays.fill(ans, 0, n, 1);
		for(int i=0; i<m; ++i)
		{
			Arrays.fill(tmp, 0, n, 0);
			if(str[i].charAt(0) == '<')
			{
				for(int j=0; j<len[i]; ++j) ans[a[i][j]] = 0;
				for(int j=0; j<len[i]; ++j) tmp[b[i][j]] = 1;
				for(int j=0; j<n; ++j) ans[j] = ans[j] & tmp[j];
			}
			else if(str[i].charAt(0) == '>')
			{
				for(int j=0; j<len[i]; ++j) tmp[a[i][j]] = 1;
				for(int j=0; j<len[i]; ++j) ans[b[i][j]] = 0;
				for(int j=0; j<n; ++j) ans[j] = ans[j] & tmp[j];
			}
			else
			{
				for(int j=0; j<len[i]; ++j) ans[a[i][j]] = 0;
				for(int j=0; j<len[i]; ++j) ans[b[i][j]] = 0;
			}
		}

		int cnt = 0, ret = -1;
		for(int i=0; i<n; ++i)
		{
			if(ans[i] == 1){ cnt++; ret = i; }
		}
		if(cnt > 1)
		{
			flag = 0;
			return -1;
		}
		else return ret;
	}
	
	public void solve()
	{
		in = new Scanner(System.in);
		while(in.hasNext())
		{
			n = in.nextInt();
			m = in.nextInt();
			
			flag = 1;
			
			for(int i=0; i<m; ++i)
			{
				int k = in.nextInt();
				len[i] = k;
				for(int j=0; j<k; ++j) a[i][j] = in.nextInt() - 1;
				for(int j=0; j<k; ++j) b[i][j] = in.nextInt() - 1;
				
				str[i] = in.next();
			}
				
			int a1 = go1();
			int a2 = go2();
			
//			System.out.println(a1 + " " + a2);
			
			if(flag == 0){ System.out.println(0); continue; }
			
			if(a1 != -1 && a2 == -1) System.out.println(a1 + 1);
			if(a1 == -1 && a1 != -1) System.out.println(a2 + 1);
			if(a1 != -1 && a2 != -1)
			{
				if(a1 == a2) System.out.println(a1 + 1);
				else System.out.println(0);
			}
			if(a1 == -1 && a2 == -1) System.out.println(0);
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
