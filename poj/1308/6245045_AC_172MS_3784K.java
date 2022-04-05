import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
	
	public class Adj
	{
		int idx;
		Adj next;
	}
	
	Adj nullNode = new Adj();
	Scanner in = null;
	Adj[] adj = new Adj[1000];
	Adj[] memo = new Adj[10000];
	int mset, size, num;
	int[] S = new int[1000];
	int[] d = new int[1000], vis = new int[1000];
	
	public int getID(int x)
	{
		for(int i=0; i<size; ++i)
		{
			if(S[i] == x) return i;
		}
		S[size] = x;
		return size++;
	}
	
	public void addEdge(int x, int y)
	{
		int a = getID(x), b = getID(y);
		Adj ptr = new Adj();
		ptr.idx = b;
		ptr.next = adj[a].next;
		adj[a].next = ptr;
		d[b]++;
	}
	
	public void init(int la, int lb)
	{
		while(true)
		{
			int a = in.nextInt(), b = in.nextInt();
			if(a == 0 && b == 0) break;
			addEdge(a, b);
		}
	}
	
	public void dfs(int now)
	{
		vis[now] = 1;
		num++;
		for(Adj ptr=adj[now].next; ptr!=null; ptr=ptr.next)
		{
			if(vis[ptr.idx] == 0) dfs(ptr.idx);
			else
			{
				num = -size * 100;
				return;
			}
		}
	}
	
	public boolean solve()
	{
		if(size == 0) return true;
		
		int cnt = 0, root = -1;
		for(int i=0; i<size; ++i)
		{
			if(d[i] == 0)
			{
				cnt++;
				root = i;
			}
		}
		if(cnt != 1) return false;
	
		Arrays.fill(vis, 0);
		num = 0;
		dfs(root);
		
		if(num != size) return false;
		else return true;
	}
	
	public void work()
	{
		in = new Scanner(System.in);
		
		int tc = 0;
		
		while(true)
		{
			int a = in.nextInt(), b = in.nextInt();
			if(a == -1) break;
			
			mset = size = 0;
			for(int i=0; i<1000; ++i)
			{
				adj[i] = new Adj();
			}
			tc++;
			if(a != 0)
			{
				Arrays.fill(d, 0);
				
				addEdge(a, b);
				init(a, b);
				
			}
			System.out.print("Case " + tc + " is");
			if(!solve()) System.out.print(" not");
			System.out.println(" a tree.");
		}
	}
	
	public static void main(String[] args)
	{
		Main a = new Main();
		a.work();
	}
}
