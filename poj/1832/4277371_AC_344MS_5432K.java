

import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	
	public Main(){
		
		T = in.nextInt();
	
		f[0] = BigInteger.ZERO;
		f[1] = BigInteger.ONE;
		
		for(int i=2; i<=129; ++i)
			f[i] = f[i-1].add(f[i-1]).add(ONE);
		
		for(int i=1; i<=T; ++i)
			solve();
	}
	
	public BigInteger min(BigInteger AA, BigInteger BB){
		if(AA.compareTo(BB)>0) return BB;
		else return AA;
	}
	
	public BigInteger figure(int[] AA){
		int i;
		opt[0][0] = BigInteger.ZERO;
		opt[0][1] = BigInteger.ZERO;
		
		
		
		for(i=1; i<=N; ++i){
			if(AA[i]==0){
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
		return opt[N][0];
	}
	
	public void solve(){
		int i;
		N = in.nextInt();
		for(i=1; i<=N; ++i)
			A[N+1-i] = in.nextInt();
		for(i=1; i<=N; ++i)
			B[N+1-i] = in.nextInt();
		
		a = figure(A);
		b = figure(B);
		if(a.compareTo(b)>0)
			System.out.println(a.add(b.multiply(NEG)));
		else System.out.println(b.add(a.multiply(NEG)));
	}
	
	private BigInteger[] f = new BigInteger[130];
	private int N, T;
	private int[] A = new int[130];
	private int[] B = new int [130];
	private BigInteger[][] opt = new BigInteger[130][2];
	private BigInteger ONE = BigInteger.ONE;
	private BigInteger NEG = new BigInteger("-1");
	private BigInteger a, b;
	private Scanner in = new Scanner(System.in);

	public static void main(String[] args) {
		Main a = new Main();
	}

}
