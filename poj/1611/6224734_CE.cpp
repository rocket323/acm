import java.util.Scanner;

public class Main {
	
	public Scanner in = null;
	public int n, m;
	public int[] p = new int[40000], num = new int[40000];
	
	public int find(int now)
	{
		if(p[now] == now) return now;
		else return p[now] = find(p[now]);
	}
	
	public void solve()
	{
//		File file = new File("1161.in");
//		try {
//			in = new Scanner(file);
//		} catch (FileNotFoundException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		
		in = new Scanner(System.in);
		
		while(true)
		{
			n = in.nextInt();
			m = in.nextInt();
			if(n == 0) break;
			
			for(int i=0; i<n; ++i){ p[i] = i; num[i] = 1; }
			
			for(int i=0; i<m; ++i)
			{
				int k = in.nextInt(), last = -1, now;
				for(int j=0; j<k; ++j)
				{
					now = in.nextInt();
					if(last == -1)
					{
//						num[find(now)]++;
						last = now;
					}
					else
					{
						int x = find(last), y = find(now);
						if(x == y) continue;
						p[x] = y;
						num[y] += num[x];
						num[x] = 0;
						last = now;
					}
				}
//				System.out.print(i + " : ");
//				for(int j=0; j<n; ++j) System.out.print(num[j] + " ");
//				System.out.println();
			}
			System.out.println(num[find(0)]);
			
//			for(int i=0; i<n; ++i) System.out.print(find(i) + " ");
//			System.out.println();
		}
	}
	
	public static void main(String[] args)
	{
		Main a = new Main();
		a.solve();
	}
}
