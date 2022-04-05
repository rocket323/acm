import java.math.BigInteger;
import java.util.Scanner;

public class Main{

    public Main(){
        N = in.nextBigInteger();
        int k = 0;
        while(N.compareTo(zero)!=0){
            solve(++k);
            N = in.nextBigInteger();
        }
    }

    int fun(BigInteger N){
        String s = N.toString();
        return s.length();
    }

    BigInteger mi(int n){
        int mid = n/2;
        if(n==1) return BigInteger.TEN;
        BigInteger tmp = mi(mid);
        if(n%2==1) return tmp.multiply(tmp).multiply(BigInteger.TEN);
        else return tmp.multiply(tmp);
    }
    
    public void solve(int tes){
	  	
        BigInteger save = new BigInteger(N+"");
        System.out.println(save);
        
        BigInteger last = BigInteger.ZERO;
        BigInteger k = BigInteger.ONE;

        System.out.print(tes+". ");
        int tmp = fun(N);
        N = N.add(mi(tmp));

        while(N.compareTo(BigInteger.ZERO)>0){
            BigInteger p = N.add(last.multiply(NEG));
            if(p.compareTo(zero)<0) p = p.add(BigInteger.TEN);
            p = p.mod(BigInteger.TEN);
            ans = ans.add(p.multiply(k));
            N = N.add(last.multiply(NEG));
            N = N.divide(BigInteger.TEN);
            k = k.multiply(BigInteger.TEN);
            last = new BigInteger(p+"");
        }

        if(fun(save)!=fun(ans)) System.out.println("IMPOSSIBLE");
        else System.out.println(ans);
        
    }
    
    private BigInteger ans = new BigInteger("0");	
    private Scanner in = new Scanner(System.in);
    private BigInteger N;
    private BigInteger NEG = new BigInteger("-1");
    private BigInteger zero = BigInteger.ZERO;

    public static void main(String[] args){
        Main a = new Main();
    }
}
