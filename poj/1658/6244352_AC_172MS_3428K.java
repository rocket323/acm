import java.util.Scanner;

public class Main {
	public static void main(String[] args)
	{
		Scanner in = new Scanner(System.in);
		
		int t = in.nextInt();
		
		while(t-- > 0)
		{
			int a = in.nextInt();
			int b = in.nextInt();
			int c = in.nextInt();
			int d = in.nextInt();
			
			if(2 * c == b + d) System.out.println(a + " " + b + " " + c + " " + d + " " + (2 * d - c));
			else System.out.println(a + " " + b + " " + c + " " + d + " " + ((long)d * d / c));
		}
	}
}
