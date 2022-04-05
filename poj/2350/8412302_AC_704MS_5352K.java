import java.util.*;

class Main
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();
		int[] a = new int[2000];

		while(t-- > 0) {
			int n = in.nextInt();
			int sum = 0, cnt = 0;
			for(int i=0; i<n; ++i) {
				a[i] = in.nextInt();
				sum += a[i];
			}
			for(int i=0; i<n; ++i) {
				if(a[i] * n > sum) cnt++;
			}
			System.out.printf("%.3f%%\n", (double)cnt * 100.0 / n);
		}
	}
}
