import java.math.BigInteger;
import java.util.Scanner;
import java.util.Arrays;

public class Main
{

	int maxl = 50010;

	long[][] c = new long[6][maxl];
	int[] a = new int[maxl];
	int[] b = new int[maxl];
	int n, sz;

	int lowbit(int n)
	{
		return n & (-n);
	}

	long get_sum(int key, int n)
	{
		n++;
		long ans = 0;
		while(n > 0)
		{
			ans += c[key][n];
			n -= lowbit(n);
		}
		return ans;
	}

	void add(int key, int n, long num)
	{
		n++;
		while(n <= sz)
		{
			c[key][n] += num;
			n += lowbit(n);
		}
	}

	int lower_bound(int x, int y, int c)
	{
		int l = x, r = y, mid, ans = -1;

		while(l <= r)
		{
			mid = (l + r) / 2;
			if(b[mid] <= c)
			{
				l = mid + 1;
				ans = mid;
			}
			else r = mid - 1;
		}
		return ans;
	}

	public void solve()
	{
		Scanner in = new Scanner(System.in);
		for(int i=0; i<=5; ++i) for(int j=0; j<maxl; ++j) c[i][j] = 0;

		while(in.hasNext())
		{
			n = in.nextInt();
			for(int i=1; i<=n; ++i)
			{
				a[i] = in.nextInt();
				b[i] = a[i];
			}

			Arrays.sort(b, 1, 1 + n);
			int x, y;
			for(x=1, y=2; y<=n; ++y)
			{
				if(b[x] != b[y]) b[++x] = b[y];
			}
			sz = x;

			for(int i=0; i<=5; ++i) Arrays.fill(c[i], 0);
			add(0, 0, 1);

			BigInteger ans = BigInteger.valueOf(0);
			for(int j=1; j<=n; ++j)
			{
				for(int i=1; i<=5; ++i)
				{
					int idx = lower_bound(1, sz, a[j]);
					long f = get_sum(i - 1, idx - 1);
					if(i == 5) ans = ans.add(BigInteger.valueOf(f));
					add(i, idx, f);
				}
			}
			System.out.println(ans);
		}
	}

	public static void main(String[] args)
	{
		Main a = new Main();
		a.solve();
	}

}

