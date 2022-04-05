import java.util.Scanner;

public class Main {
	public static void main(String[] args)
	{
		int last = 0;
		Scanner in = new Scanner(System.in);
		
		while(true)
		{
			int n = in.nextInt();
			if(n == -1) break;
			
			int ans = 0, a, b;
			
			last = 0;
			for(int i=0; i<n; ++i)
			{
				a = in.nextInt();
				b = in.nextInt();
				
				ans += (b - last) * a;
				last = b;
			}
			
			System.out.println(ans + " miles");
		}
	}
}
