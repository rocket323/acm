

import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	
	public Main(){
		Scanner in = new Scanner(System.in);
		N = in.nextInt();
		for(int i=1; i<=N; ++i){
			A[i] = in.nextInt();
			if(A[i]==1) last = i;
		}
	}
	
	public BigInteger min(BigInteger A, BigInteger B){
		if(A.compareTo(B)>0) return B;
		else return A;
	}
	
	public void solve(){
		int i;
		f[0] = BigInteger.ZERO;
		f[1] = BigInteger.ONE;
		for(i=2; i<=N; ++i)
			f[i] = f[i-1].multiply(new BigInteger("2").add(ONE));
		
		i=1; 
		while(A[i]==0&&i<=N) ++i;
		if(i==N+1){
			System.out.println(0);
			return;
		}
	
		opt[0][0] = BigInteger.ZERO;
		opt[0][1] = BigInteger.ZERO;
		
		for(i=1; i<=last; ++i){
			if(A[i]==0){
				opt[i][0] = min(opt[i-1][1].add(f[i-1]), opt[i-1][0]);
				
				opt[i][1] = min(opt[i-1][1].add(ONE).add(f[i-1]),
								opt[i-1][0].add(f[i-1]).add(f[i-1].add(ONE)));
			}
			else{
				opt[i][0] = min(opt[i-1][1].add(f[i-1]).add(ONE),
								opt[i-1][0].add(f[i-1]).add(f[i-1]).add(ONE));
				
				opt[i][1] = min(opt[i-1][1].add(f[i-1]), opt[i-1][0]);
				
			}
		}
		System.out.println(opt[last][0]);
	}
	
	private int[] A = new int[1001];
	private int N;
	private int last;
	private BigInteger[] f = new BigInteger[1001];
	private BigInteger[][] opt = new BigInteger[1001][2];
	private BigInteger ONE = BigInteger.ONE;
	
	public static void main(String[] args){
		Main a = new Main();
		a.solve();
	}
}
