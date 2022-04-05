import java.util.Scanner;

public class Main {
	
	public Scanner in = null;
	
	public boolean isVowel(char ch)
	{
		if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') return true;
		else return false;
	}
	
	public boolean check1(String str)
	{
		int cnt = 0;
		for(int i=0; i<str.length(); ++i)
		{
			if(isVowel(str.charAt(i))) cnt++;
		}
		if(cnt > 0) return true;
		else return false;
	}
	
	public boolean check2(String str)
	{
		for(int i=0; i<=str.length()-3; ++i)
		{
			char ch1 = str.charAt(i), ch2 = str.charAt(i+1), ch3 = str.charAt(i+2);
			if(isVowel(ch1) && isVowel(ch2) && isVowel(ch3)) return false;
			if(!isVowel(ch1) && !isVowel(ch2) && !isVowel(ch3)) return false;
		}
		return true;
	}
	
	public boolean check3(String str)
	{
		for(int i=0; i<=str.length()-2; ++i)
		{
			char ch1 = str.charAt(i), ch2 = str.charAt(i+1);
			if(ch1 == 'e' && ch2 == 'e') continue;
			if(ch1 == 'o' && ch2 == 'o') continue;
			if(ch1 == ch2) return false;
		}
		return true;
	}
	
	public void solve()
	{
		in = new Scanner(System.in);
		
		while(true)
		{
			String str = in.next();
			if(str.compareTo("end") == 0) break;
			
			System.out.print("<" + str + "> " + "is ");
			
			if(check1(str) && check2(str) && check3(str)) System.out.println("acceptable.");
			else System.out.println("not acceptable.");
		}
	}
	
	public static void main(String[] args)
	{
		Main a = new Main();
		a.solve();
	}
}
